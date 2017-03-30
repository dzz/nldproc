#include "processor.h"

namespace nldproc {
    void processor::process(stereo_buffer input, stereo_buffer output) {
        for( channel_index idx = 0; idx<2; ++idx) {
            this->process_channel(idx, input[idx],output[idx]);
        }
    }
}
