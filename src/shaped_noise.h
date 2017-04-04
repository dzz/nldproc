#pragma once
#include "whitenoise.h"
#include "DspFilters/Dsp.h"

namespace nldproc {

    typedef Dsp::SimpleFilter <Dsp::ChebyshevI::LowPass<3>, 2> sn_lpf_filter;

    class shaped_noise : public processor {
        public:
            shaped_noise();
            virtual void process(stereo_buffer input, stereo_buffer output);
        private:
            sn_lpf_filter lpf_filter;
    };
}
