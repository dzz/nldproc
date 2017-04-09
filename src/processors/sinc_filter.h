#pragma once

#include "fir.h"

namespace nldproc {

    typedef double fs_ratio;

    typedef unsigned sinc_filter_mode;

    const unsigned int SINC_LOWPASS = 0;
    const unsigned int SINC_HIPASS = 1;

    class sinc_filter : public fir {
        public:
            sinc_filter( tapcount taps, fs_ratio cutoff, sinc_filter_mode mode );
    };
}
