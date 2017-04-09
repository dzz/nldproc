#include "derivative.h"
#include "environment.h"

namespace nldproc {
    derivative::derivative() {
        i[0] = 0;
        i[1] = 0;
    }

    void derivative::process_channel( channel_index channel, single_channel input, single_channel output ) {
        for(sample_index idx=0; idx< environment::get_buffer_chunksize(); ++idx) {
            output[idx] = input[idx]-i[channel];
            i[channel] = input[idx];
        }
    }
}
