#include "processor.h"
#include "environment.h"
#include "downmixer.h"

namespace nldproc {

    void downmixer::process(stereo_buffer input, stereo_buffer output ) {
        sample_index        position        = 0;
        sample_index        total_samples   = environment::get_buffer_chunksize();

        double x;

        while(position < total_samples) {
            x = 0.5 * ( input[0][position] + input[1][position] );
            output[0][position] = x;
            output[1][position++] = x;
        }
    };
}

