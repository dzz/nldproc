#include "shaped_noise.h"
#include "whitenoise.h"

namespace nldproc {

    const double noise_shaping_lpf_cutoff = 20000.0f;

    double get_buffer_chunksize();

    void shaped_noise::process(stereo_buffer input, stereo_buffer output ) {
        whitenoise::fill_buffer( output );
        lpf_filter.process( environment::get_buffer_chunksize(), output );
    }

    shaped_noise::shaped_noise() {
        lpf_filter.setup( 3, environment::get_samplerate(), noise_shaping_lpf_cutoff, 2.0 );
    }
}
