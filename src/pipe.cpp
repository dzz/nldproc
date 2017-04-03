#include "pipe.h"
#include "processor.h"
#include "environment.h"
#include "controls.h"

#include "DspFilters/Dsp.h"

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

    void pipe::create_oversampler( alias name, os_factor amount ) {
        this->oversamplers[name] = new oversampler();
        environment::set_oversampling( amount );
        this->oversamplers[name]->setup(  resampling_filter_order, environment::get_samplerate(), resampling_filter_freq );

        environment::set_oversampling( 1 );

        std::cout<<"created oversampling filter at:"<<this->oversamplers[name]<<"\n;";
    }

    void pipe::create_downsampler( alias name, os_factor amount) {
        this->downsamplers[name] = new downsampler();
        environment::set_oversampling( amount );
        this->downsamplers[name]->setup( resampling_filter_order, environment::get_samplerate(), resampling_filter_freq );
        environment::set_oversampling( 1 );

        std::cout<<"created downsampling filter at:"<<this->downsamplers[name]<<"\n;";
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

        for(sample_index idx = 0;idx < environment::get_buffer_chunksize(); ++idx) {
            buffer[0][idx] = 0.0;
            buffer[1][idx] = 0.0;
        }

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
                            std::cout<<"created buffer :"<<alias<<"\n";
                            std::cout<<"buffer  addr   :"<<&buffer<<"\n";
                            std::cout<<"base_chunksize :"<<environment::get_base_buffer_chunksize()<<"\n";
                            std::cout<<"chunksize      :"<<environment::get_buffer_chunksize()<<"\n";
                            this->buffers[alias] = buffer;
                       });

    }



    void pipe::oversample_into( alias from, alias to, os_factor amount, alias oversampler ) {

        auto down = this->buffers[ from ];
        auto up = this->buffers[ to ];
        sample_index idx;
        auto write_idx = 0;

        std::cout<<"oversample from   :"<<down<<"\n";
        std::cout<<"oversample to     :"<<up<<"\n";
        std::cout<<"oversample amt    :"<<amount<<"\n";

        environment::set_oversampling( amount );
        
        for(idx = 0; idx< environment::get_buffer_chunksize(); ++idx) {
            write_idx = idx / amount;
            if(idx%amount==0) {
                up[0][idx] = down[0][write_idx];
                up[1][idx] = down[0][write_idx];
            } else {
                up[0][idx] = 0;
                up[1][idx] = 0;
            }
        }

        std::cout<<"filtering with:"<<oversampler<<" at "<<this->oversamplers[oversampler]<<"\n";
        this->oversamplers[oversampler]->process( environment::get_buffer_chunksize(), up );
        std::cout<<"upsampled\n";
        
    }

    void pipe::downsample_into( alias buffer_from, alias buffer_to, alias downsampler ) {
        auto from               = this->buffers[ buffer_from ];
        auto to                 = this->buffers[ buffer_to ];
        auto filter             = this->downsamplers[downsampler];

        std::cout<<"downsample from   :"<<from<<"\n";
        std::cout<<"downsample to     :"<<to<<"\n";

        sample_index to_idx = 0;
        sample_index idx;

        os_factor amount = environment::get_oversampling();

        filter->process(environment::get_buffer_chunksize(), from);

        for(idx = 0; idx< environment::get_buffer_chunksize(); idx+=amount) {
            to[0][to_idx] = from[0][idx];
            to[1][to_idx] = from[1][idx];
            to_idx++;
        }

        environment::set_oversampling(1);

    }


    void pipe::create_oversampled_buffer( alias_list aliases, os_factor amount ) {
        environment::set_oversampling( amount );
        this->create_buffer( aliases );
        environment::set_oversampling( 1 );
    }

    void pipe::assign_ptr_buffer( alias_list aliases, stereo_buffer buffer ) {
        std::for_each( aliases.begin(),
                       aliases.end(),
                       [ this, buffer ]( auto alias ) {
                            this->buffers[alias] = buffer;
                       });
    }

    pipe::~pipe() {

        std::for_each( this->oversamplers.begin(),
                       this->oversamplers.end(),
                       [ this ]( auto pair ) {
                            delete pair.second;
                       });

        std::for_each( this->downsamplers.begin(),
                       this->downsamplers.end(),
                       [ this ]( auto pair ) {
                            delete pair.second;
                       });

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

    void pipe::write_buffer( alias buffer_alias, filename output_file, filetype output_type ) {
        std::ofstream file( output_file, std::ios::out | std::ios::binary );
        stereo_buffer output_buffer = this->get_mapped_buffer( buffer_alias );

        sample_index idx = 0;
        while(idx < environment::get_buffer_chunksize()) {

            if( output_type == binary_stereo ) {
                double stereo_sample[2];
                stereo_sample[0] = output_buffer[0][idx];
                stereo_sample[1] = output_buffer[0][idx];
                idx++;

                file.write( reinterpret_cast<char *>(&stereo_sample), sizeof(stereo_sample) );
            }

            if( (output_type == binary_left) || (output_type == binary_right ) ) {
                double mono_sample;

                if(output_type == binary_left) {
                    mono_sample = output_buffer[0][idx];
                } else {
                    mono_sample = output_buffer[1][idx];
                }
                idx++;
                file.write( reinterpret_cast<char *>(&mono_sample), sizeof(mono_sample) );
            }
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

