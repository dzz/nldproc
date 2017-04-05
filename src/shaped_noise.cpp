#include "shaped_noise.h"
#include "whitenoise.h"

namespace nldproc {

    const double noise_shaping_lpf_cutoff = 10000.0f;

    double get_buffer_chunksize();

    void shaped_noise::process(stereo_buffer input, stereo_buffer output ) {
        whitenoise::fill_buffer( output );

        lpf_filter_0.process( environment::get_buffer_chunksize(), output );
        lpf_filter_1.process( environment::get_buffer_chunksize(), output );
        lpf_filter_2.process( environment::get_buffer_chunksize(), output );
    }

    shaped_noise::shaped_noise() {
        lpf_filter_0.setup( 5, environment::get_samplerate(), noise_shaping_lpf_cutoff );
        lpf_filter_1.setup( 5, environment::get_samplerate(), noise_shaping_lpf_cutoff * 0.5 );
        lpf_filter_2.setup( 5, environment::get_samplerate(), noise_shaping_lpf_cutoff * 0.25 );
    }
}
