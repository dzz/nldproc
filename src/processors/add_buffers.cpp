#include "add_buffers.h"
#include "environment.h"

namespace nldproc {

    void add_buffers::process(stereo_buffer input, stereo_buffer output ) {
            for(sample_index idx = 0; idx< environment::get_buffer_chunksize(); ++idx) {
                output[0][idx] += input[0][idx];
                output[1][idx] += input[1][idx];
            }
    }

}
