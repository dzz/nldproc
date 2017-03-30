#include "pipe.h"
#include "processor.h"
#include "environment.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

namespace nldproc {

    void pipe::map_processor( processor* processor, std::string name ) {
        this->processors[ name ] = processor;
    }

    void pipe::create_buffer( std::vector<std::string> aliases ) {
        stereo_buffer buffer;

        buffer = (double**) new double[ environment::get_buffer_chunksize() * 2 ];

        std::for_each( aliases.begin(),
                       aliases.end(),
                       [ this, buffer ]( auto alias ) {
                            this->buffers[alias] = buffer;
                       });

        this->unique_buffers.push_back( buffer );
    }

    pipe::~pipe() {
        std::for_each( this->unique_buffers.begin(),
                       this->unique_buffers.end(),
                       [ this ]( auto buffer ) {
                            delete buffer;
                       });
    }

    void pipe::process_with( std::string processor, std::string buffer_from,std::string buffer_to ) {

        auto processor_object = this->processors [ processor ];
        auto from = this->buffers[ buffer_from ];
        auto to = this->buffers[ buffer_to ];

        processor_object->process( from, to );
    }
}

