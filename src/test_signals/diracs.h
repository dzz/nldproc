#include "test_signal.h"
#include "environment.h"
#include "processor.h"
#include "pipe.h"

namespace nldproc {

    typedef sample_index sample_spacing;

    class diracs : public test_signal {
            public:
                static void fill_range( sample_spacing dirac_spacing, sample dirac_amplitude, stereo_buffer channels, sample_index start, sample_index end);
    };
}

