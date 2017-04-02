#pragma once

#include <string>

namespace nldproc {

    typedef unsigned int buffer_chunksize;
    typedef unsigned int sample_index;
    typedef unsigned int samplerate;
    typedef std::string filename;

    class environment {
        public:
            static void write_to_file( filename output_file );       
            static samplerate          get_samplerate();
            static buffer_chunksize    get_buffer_chunksize();
    };
}
