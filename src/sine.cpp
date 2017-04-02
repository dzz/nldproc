#include "sine.h"
#include "environment.h"
#include "processor.h"

#include <cmath>

namespace nldproc {

    void sine::generate(double hz, buffer_chunksize samples, single_channel channel) {
        for(sample_index i=0; i<samples;++i) {
            channel[i] = sin( ((double)i / environment::get_samplerate() ) * hz );
        }
    }

    void sine::fill_buffer( double hz, stereo_buffer channels ) {
        sine::generate( hz, environment::get_buffer_chunksize(), channels[0] );
        sine::generate( hz, environment::get_buffer_chunksize(), channels[1] );
    }
}
