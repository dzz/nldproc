#include "processor.h"
#include "pipe.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

namespace nldproc {

    pipe::map_processor( processor processor, std::string name ) {
        this->processors[ name ] = processor;
    }

    pipe::set_chunksize( buffer_chunksize size ) {
        this->chunk_size = size;
    }

    pipe::create_buffer( vector<std::string> aliases ) {
        stereo_buffer buffer;
        buffer = new double[2][ this->chunk_size ];

        std::for_each( aliases->begin(),
                       aliases->end(),
                       [ this ]( auto alias ) {
                            this->buffers[alias] = buffer;
                       });

        this->unique_buffers.push_back( buffer );
    }

    pipe::~pipe() {
        std::for_each( this->unique_buffers.begin(),
                       this->unique_buffers.end(),
                       [ this ]( auto buffer ) {
                            buffer->delete();
                       });
    }

    pipe::process_with( std::string processor, std::string buffer_from,std::string_buffer_to ) {

        auto processor = this->processors [ processor ];
        auto buffer_from = this->buffers[ buffer_from ];
        auto buffer_to = this->buffers[ buffer_to ];

        processor->process( buffer_from, buffer_to );
    }
}

