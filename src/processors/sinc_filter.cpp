#include "sinc_filter.h"
#include "utils/sinc.h"

namespace nldproc {

    sinc_filter::sinc_filter(tapcount taps, fs_ratio cutoff, sinc_filter_mode mode) {
        double *sincFilter = new double[taps];

        if(mode==SINC_LOWPASS) {
            wsfirLP( sincFilter, taps, W_BLACKMAN, cutoff );
        }
        if(mode==SINC_HIPASS) {
            wsfirHP(sincFilter,taps, W_BLACKMAN, cutoff );
        }
        this->configure(taps, sincFilter);

        delete sincFilter;
    }
}

