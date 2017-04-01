#pragma once

#include "environment.h"
#include "controls.h"
#include "processor.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

namespace nldproc {

    typedef std::string alias;
    typedef std::vector<alias> alias_list;
    typedef std::unordered_map< alis, processor* > processor_map;
    typedef std::unordered_map< alis, stereo_buffer > buffer_map;
    typedef std::vector< stereo_buffer > buffer_collection;
    
    struct parameter_dispath {
        std::function<double(double)> transform;
        control* dispatch_target;
    }

    typedef std::vector< parameter_dispath > parameter;
    typedef std::unordered_map< alias, parameter > parameter_map;

    class pipe {
        public:
            pipe();
            ~pipe();
            
            control* get_control( alias processor, control_name control);
            void map_parameter( alias processor, alias parameter, alias 
            void map_processor( processor* processor, alias name );
            void create_buffer( alias_list aliases  );
            void assign_ptr_buffer( alias_list aliases, stereo_buffer buffer );
            void process_with( alias processor, alias buffer_from, alias buffer_to );
            void process( stereo_buffer buffer );
            stereo_buffer create_unmapped_buffer();
            stereo_buffer get_mapped_buffer( alias alias );
            void dump_buffer( alias alias );
        private:
            processor_map processors;
            buffer_map buffers;
            buffer_collection unique_buffers;
            buffer_chunksize chunk_size;
            parameter_collection parameters;
            static void delete_unmapped_buffer( stereo_buffer buffer );
    }; 
}
