#include "integrator.h"
#include "environment.h"

namespace nldproc {
    integrator::integrator() {
        i[0] = 0;
        i[1] = 0;
    }

    void integrator::process_channel( channel_index channel, single_channel input, single_channel output ) {
        for(sample_index idx=0; idx< environment::get_buffer_chunksize(); ++idx) {
            i[channel]+=input[idx]*0.5;
            output[idx] = i[channel];
            i[channel]*=0.5;
        }
    }
}
