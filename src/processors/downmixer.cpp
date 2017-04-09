#include "processor.h"
#include "environment.h"
#include "downmixer.h"
#include "utils/volume.h"

namespace nldproc {

    downmixer::downmixer() {
        factor = 0.5;
    }

    downmixer::downmixer( downmix_mode mode ) {
        if(mode == DOWNMIX_HALF_AMP) 
            factor = 0.5;
        if(mode == DOWNMIX_NEG6_DB )
            factor = volume::db2vol( -6 );
        if(mode == DOWNMIX_SQRT2_2 )
            factor = 0.70710678118654752440084436210485;
    }

    void downmixer::process(stereo_buffer input, stereo_buffer output ) {
        sample_index        position        = 0;
        sample_index        total_samples   = environment::get_buffer_chunksize();

        double x;

        while(position < total_samples) {
            x = factor * ( input[0][position] + input[1][position] );
            output[0][position] = x;
            output[1][position++] = x;
        }
    };
}

