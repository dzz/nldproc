#include "processor.h"
#include "environment.h"
#include "upmixer.h"

namespace nldproc {

    void upmixer::process(stereo_buffer input, stereo_buffer output ) {
        sample_index        position        = 0;
        sample_index        total_samples   = environment::get_buffer_chunksize();

        if( input != output ) {
            while(position < total_samples) {
                output[0][position] = input[0][position];
                output[1][position] = input[0][position];
                position++;
            }
        } else {
            while(position < total_samples) {
                output[1][position] = input[0][position];
                position++;
            }
        }
    }

}

