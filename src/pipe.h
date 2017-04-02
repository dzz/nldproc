#pragma once

#include "environment.h"
#include "controls.h"
#include "processor.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

namespace nldproc {

    typedef unsigned int filetype;

    const filetype binary_stereo = 0;
    const filetype binary_left = 2;
    const filetype binary_right = 3;


    typedef std::string alias;
    typedef std::vector<alias> alias_list;
    typedef std::unordered_map< alias, processor* > processor_map;
    typedef std::unordered_map< alias, stereo_buffer > buffer_map;
    typedef std::vector< stereo_buffer > buffer_collection;
    typedef std::string filename;
    
    struct parameter_dispatch {
        std::function<double(double)> transform;
        control* target;
    };

    typedef std::vector< parameter_dispatch > parameter;
    typedef std::vector< parameter_dispatch > parameter_dispatches;
    typedef std::unordered_map< alias, parameter > parameter_map;

    class pipe {
        public:
            pipe();
            ~pipe();
            
            control* get_control( alias processor, control_name control);
            void create_parameter( alias name, parameter parameter );

            void set_parameter( alias parameter, double value );
            void map_processor( processor* processor, alias name );
            void create_buffer( alias_list aliases  );
            void assign_ptr_buffer( alias_list aliases, stereo_buffer buffer );
            void process_with( alias processor, alias buffer_from, alias buffer_to );
            void process( stereo_buffer buffer );
            stereo_buffer create_unmapped_buffer();
            stereo_buffer get_mapped_buffer( alias alias );
            void dump_buffer( alias buffer_alias );
            void write_buffer( alias buffer_alias, filename output_file, filetype output_type );
        private:
            processor_map processors;
            buffer_map buffers;
            buffer_collection unique_buffers;
            buffer_chunksize chunk_size;
            parameter_map parameters;
            static void delete_unmapped_buffer( stereo_buffer buffer );
    }; 
}
