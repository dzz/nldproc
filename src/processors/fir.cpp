#include "fir.h"

namespace nldproc {

    fir::fir( tapcount size, coefficients spec) {
        inputs[0] = new sample[size];
        inputs[1] = new sample[size];
        filter = new coefficient[size];
        for(sample_index i=0; i< size; ++i) {
            filter[i] = spec[i];
            inputs[0][i] = 0.0;
            inputs[1][i]=  0.0;
        }
        filter_size = size;
    }


    void fir::process_channel( channel_index channel, single_channel input, single_channel output ) {
        for(sample_index idx = 0; idx<environment::get_buffer_chunksize();++idx) {
            for(tapcount t_idx =1; t_idx<filter_size;++t_idx) {
                inputs[channel][t_idx] = inputs[channel][t_idx-1];
            }
            inputs[channel][0] = input[idx];
            output[idx] = 0.0;
            for(tapcount t_idx = 0; t_idx < filter_size; ++t_idx) {
                output[idx]+= inputs[channel][t_idx] * this->filter[t_idx];
            }
        }
    }

    fir::~fir() {
        delete inputs[0];
        delete inputs[1];
        delete filter;
    }

}
