#include "shaped_noise.h"
#include "whitenoise.h"

namespace nldproc {

    const double noise_shaping_lpf_cutoff = 10000.0f;
    const double noise_shaping_hpf_cutoff = 4000.0f;

    double get_buffer_chunksize();

    void shaped_noise::process(stereo_buffer input, stereo_buffer output ) {
        whitenoise::fill_buffer( output );

        if(mode==lf_noise) {
            lpf_filter.process( environment::get_buffer_chunksize(), output );
        }
        if(mode==hf_noise) {
            hpf_filter.process( environment::get_buffer_chunksize(), output );
        }
    }

    shaped_noise::shaped_noise(shaped_noise_mode mode) {

        this->mode = mode;

        lpf_filter.setup( NLDPROC_NOISE_SHAPING_FILTER_ORDER, environment::get_samplerate(), noise_shaping_lpf_cutoff );
        hpf_filter.setup( NLDPROC_NOISE_SHAPING_FILTER_ORDER, environment::get_samplerate(), noise_shaping_lpf_cutoff );
    }
}
