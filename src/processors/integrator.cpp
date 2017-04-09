#include "integrator.h"
#include "environment.h"
#include <cmath>

namespace nldproc {
    integrator::integrator(time_seconds time) {
        i[0] = 0;
        i[1] = 0;

        double e = exp(1.0);
        
        g = pow(e,( -1 / (time * environment::get_samplerate())));
        std::cout<<"G:"<<g<<"\n";
    }

    void integrator::process_channel( channel_index channel, single_channel input, single_channel output ) {
        for(sample_index idx=0; idx< environment::get_buffer_chunksize(); ++idx) {
            output[idx] = input[idx] + g*(i[channel]-input[idx]);
            i[channel] = output[idx];
        }
    }
}
