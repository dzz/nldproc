#pragma once

namespace nldproc {

    typedef unsigned int buffer_chunksize;
    typedef unsigned int sample_index;
    typedef unsigned int samplerate;

    class environment {

        public:
            static samplerate          get_samplerate();
            static buffer_chunksize    get_buffer_chunksize();
    };
}
