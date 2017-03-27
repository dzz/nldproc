#include <string>
#include "processor.h"

namespace nldproc{

    typedef unsigned int buffer_chunksize
    typedef unsigned int buffer_ID;

    class buffers {

        public:
            void set_chunksize(buffer_chunksize size);
            void create_ptrinput_buffer( std::string name );
            void create_memory_buffer( std::string name ); 
            void create_alias_buffer_from_to(std:string from, std::string to);
            void arm_ptrinput_buffer(std::string name, stereo_buffer channels );
            void process_to_with_from(std::string to, processor processor, std::string from);
            void multiply_right(std:string left, std::string right);
            void process_in_place_with( std::string buffer, processor processor );
            void clone_from_to(std::string from, std::string to);
        private:
            buffer_ID seed;
    };
}
