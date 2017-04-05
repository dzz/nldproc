#pragma once
#include "whitenoise.h"
#include "DspFilters/Dsp.h"

#define NLDPROC_NOISE_SHAPING_FILTER_ORDER 8

namespace nldproc {

    typedef unsigned int shaped_noise_mode;
    
    const shaped_noise_mode lf_noise = 0;
    const shaped_noise_mode hf_noise = 1;

    typedef Dsp::SimpleFilter <Dsp::Bessel::LowPass<NLDPROC_NOISE_SHAPING_FILTER_ORDER>, 2> sn_lpf_filter;
    typedef Dsp::SimpleFilter <Dsp::Bessel::HighPass<NLDPROC_NOISE_SHAPING_FILTER_ORDER>, 2> sn_hpf_filter;

    class shaped_noise : public processor {
        public:
            shaped_noise(shaped_noise_mode mode);
            virtual void process(stereo_buffer input, stereo_buffer output);
        private:
            shaped_noise_mode mode;
            sn_lpf_filter lpf_filter;
            sn_hpf_filter hpf_filter;
    };
}
