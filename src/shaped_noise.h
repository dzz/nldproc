#pragma once
#include "whitenoise.h"
#include "DspFilters/Dsp.h"

namespace nldproc {

    typedef Dsp::SimpleFilter <Dsp::Bessel::LowPass<5>, 2> sn_lpf_filter;

    class shaped_noise : public processor {
        public:
            shaped_noise();
            virtual void process(stereo_buffer input, stereo_buffer output);
        private:
            sn_lpf_filter lpf_filter_0;
            sn_lpf_filter lpf_filter_1;
            sn_lpf_filter lpf_filter_2;
    };
}
