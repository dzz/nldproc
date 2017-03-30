#pragma once

#include "environment.h"
#include "processor.h"
#include <string>
#include <unordered_map>
#include <vector>

namespace nldproc {

    typedef std::string alias;
    typedef std::vector<alias> alias_list;

    class pipe {
        public:
            pipe();
            ~pipe();
            void map_processor( processor* processor, alias name );
            void create_buffer( alias_list aliases  );
            void assign_ptr_buffer( alias_list aliases, stereo_buffer buffer );
            void process_with( alias processor, alias buffer_from, alias buffer_to );
            void process( stereo_buffer buffer );
            stereo_buffer create_unmapped_buffer();
            stereo_buffer get_mapped_buffer( alias alias );
            void dump_buffer( alias alias );
        private:
            std::unordered_map< alias, processor* > processors;
            std::unordered_map< alias, stereo_buffer > buffers;
            std::vector< stereo_buffer > unique_buffers;
            buffer_chunksize chunk_size;
            static void delete_unmapped_buffer( stereo_buffer buffer );
            
    }; 
}
