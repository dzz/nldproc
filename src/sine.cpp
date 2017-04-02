#include "sine.h"
#include "environment.h"
#include "processor.h"

#include <cmath>

namespace nldproc {

constexpr double pi() { return std::atan(1)*4; }

    void sine::generate(double hz, buffer_chunksize samples, single_channel channel) {
        for(sample_index i=0; i<samples;++i) {

            double t = (double)i / (double)environment::get_samplerate();
            channel[i] = sin( t*hz*2*pi() );
        }
    }

    void sine::fill_buffer( double hz, stereo_buffer channels ) {
        sine::generate( hz, environment::get_buffer_chunksize(), channels[0] );
        sine::generate( hz, environment::get_buffer_chunksize(), channels[1] );
    }
}
