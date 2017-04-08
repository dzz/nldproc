#include "clone_buffer.h"
#include "environment.h"

namespace nldproc {

    void clone_buffer::process(stereo_buffer input, stereo_buffer output ) {
            for(sample_index idx = 0; idx< environment::get_buffer_chunksize(); ++idx) {
                output[0][idx] = input[0][idx];
                output[1][idx] = input[1][idx];
            }
    }

}
