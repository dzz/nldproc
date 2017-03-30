#pragma once

namespace nldproc {

    typedef double**     stereo_buffer;
    typedef double*      single_channel;
    typedef unsigned int channel_index;
    typedef double*      sample_addr;
          
    class processor {
        public:
            virtual void process(stereo_buffer input, stereo_buffer output);
        private:
            virtual void process_channel(channel_index index, single_channel input, single_channel output) = 0;
    };
}
