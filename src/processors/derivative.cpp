#include "derivative.h"
#include "environment.h"

namespace nldproc {
    derivative::derivative() {
        i[0] = 0;
        i[1] = 0;

        t = 1.0 / environment::get_samplerate();

        norm_factor = 1.0/(1.0/t);
    }

    void derivative::process_channel( channel_index channel, single_channel input, single_channel output ) {
        double tmp = 0;
        for(sample_index idx=0; idx< environment::get_buffer_chunksize(); ++idx) {
            tmp = input[idx];
            output[idx] = ((input[idx]-i[channel]) / t) * norm_factor;
            i[channel] = tmp;
        }
    }
}
