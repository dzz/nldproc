#include "pipe.h"
#include "processor.h"
#include "environment.h"
#include "controls.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

namespace nldproc {

    pipe::pipe() {
        this->chunk_size = environment::get_buffer_chunksize();
    }

    void pipe::map_processor( processor* processor, alias name ) {
        this->processors[ name ] = processor;
    }

    control* pipe::get_control( alias processor, control_name control ) {
        return this->processors[processor]->get_control( control );
    }

    stereo_buffer pipe::create_unmapped_buffer() {
        double** buffer = new double*[2];

        buffer[0] = new double[ environment::get_buffer_chunksize() ];
        buffer[1] = new double[ environment::get_buffer_chunksize() ];

        this->unique_buffers.push_back( buffer );
        return buffer; 
    }

    void pipe::delete_unmapped_buffer( stereo_buffer buffer ) {
        delete buffer[0];
        delete buffer[1];
        delete buffer;
    }

    void pipe::create_buffer( alias_list aliases ) {
        stereo_buffer buffer;

        buffer      = this->create_unmapped_buffer();

        std::for_each( aliases.begin(),
                       aliases.end(),
                       [ this, buffer ]( auto alias ) {
                            this->buffers[alias] = buffer;
                       });

    }

    void pipe::assign_ptr_buffer( alias_list aliases, stereo_buffer buffer ) {
        std::for_each( aliases.begin(),
                       aliases.end(),
                       [ this, buffer ]( auto alias ) {
                            this->buffers[alias] = buffer;
                       });
    }

    pipe::~pipe() {
        std::for_each( this->unique_buffers.begin(),
                       this->unique_buffers.end(),
                       [ this ]( auto buffer ) {
                            pipe::delete_unmapped_buffer( buffer );
                       });
    }

    void pipe::process_with( alias processor, alias buffer_from,alias buffer_to ) {

        auto processor_object   = this->processors [ processor ];
        auto from               = this->buffers[ buffer_from ];
        auto to                 = this->buffers[ buffer_to ];

        processor_object->process( from, to );
    }

    stereo_buffer pipe::get_mapped_buffer( alias buffer_alias) { 
        return this->buffers[buffer_alias];
    }

    void pipe::dump_buffer( alias buffer_alias ) {
        stereo_buffer buffer = this->get_mapped_buffer( buffer_alias );
        for( sample_index idx = 0; idx < environment::get_buffer_chunksize(); ++idx) {
            std::cout<<buffer[0][idx]<<","<<buffer[1][idx]<<"\n";
        }
    }

    void pipe::write_buffer( alias buffer_alias, filename output_file ) {
        std::ofstream file( output_file, std::ios::out | std::ios::binary );
        stereo_buffer output_buffer = this->get_mapped_buffer( buffer_alias );

        sample_index idx = 0;
        while(idx < environment::get_buffer_chunksize()) {
            double stereo_sample[2];
            stereo_sample[0] = output_buffer[0][idx];
            stereo_sample[1] = output_buffer[0][idx];
            idx++;

            file.write( reinterpret_cast<char *>(&stereo_sample), sizeof(stereo_sample) );
            
        }
        file.close();
    }

    void pipe::set_parameter( alias name, double value ) {
        parameter_dispatches dispatches = this->parameters[name];

        std::for_each( dispatches.begin(),
                       dispatches.end(),
                       [value](auto dispatch) {
                            dispatch.target->impulse = dispatch.transform(value);
                            //std::cout<<"control dispatch :"<<dispatch.target<<"\n";
                            //std::cout<<"issuing impulse :"<<dispatch.target->impulse<<"\n";
                       } );
    }

    void pipe::create_parameter( alias name, parameter parameter ) {
        this->parameters[name] = parameter;
    } 
}

