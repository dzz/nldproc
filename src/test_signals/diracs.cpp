#include "diracs.h"

namespace nldproc {

    void diracs::fill_range( sample_spacing dirac_spacing, sample dirac_amplitude, stereo_buffer channels, sample_index start, sample_index end ) {

        for(sample_index idx = start; idx<end; idx++) {
            channels[0][idx] = 0.0;
            channels[1][idx] = 0.0;
        }

        for(sample_index idx = start; idx<end; idx+=dirac_spacing) {
            channels[0][idx] = dirac_amplitude;
            channels[1][idx] = dirac_amplitude;
        }
    }
}
