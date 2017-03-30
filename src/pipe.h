#pragma once

#include "environment.h"
#include "processor.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace nldproc {

    class pipe {
        public:
            ~pipe();
            void set_chunksize( buffer_chunksize size );
            void map_processor( processor processor, std::string name );
            void create_buffer( vector< std::string > aliases  );
            void process_with( std::string processor, std::string buffer_from, std::string buffer_to );
        private:
            std::unordered_map< std::string, processor > processors;
            std::unordered_map< std::string, stereo_buffer > buffers;
            std::vector< stereo_buffer > unique_buffers;
            buffer_chunksize chunk_size;
            
    }; 
}
