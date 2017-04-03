#pragma once

#include <string>

namespace nldproc {

    typedef unsigned int buffer_chunksize;
    typedef unsigned int sample_index;
    typedef unsigned int samplerate;
    typedef unsigned int os_factor;
    typedef std::string filename;

    class environment {
        public:
            static void write_to_file( filename output_file );       
            static samplerate          get_samplerate();
            static samplerate          get_base_samplerate();
            static buffer_chunksize    get_buffer_chunksize();
            static buffer_chunksize    get_base_buffer_chunksize();
            static void                set_oversampling(os_factor amount);
            static os_factor           get_oversampling();
    };
}
