#pragma once

#include "environment.h"
#include "processor.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace nldproc {

    class pipe {
        public:
            pipe();
            ~pipe();
            void map_processor( processor* processor, std::string name );
            void create_buffer( std::vector< std::string > aliases  );
            void assign_ptr_buffer( std::vector< std::string > aliases, stereo_buffer buffer );
            void process_with( std::string processor, std::string buffer_from, std::string buffer_to );
            void process( stereo_buffer buffer );
            stereo_buffer create_unmapped_buffer();
        private:
            std::unordered_map< std::string, processor* > processors;
            std::unordered_map< std::string, stereo_buffer > buffers;
            std::vector< stereo_buffer > unique_buffers;
            buffer_chunksize chunk_size;
            static void delete_unmapped_buffer( stereo_buffer buffer );
            
    }; 
}
