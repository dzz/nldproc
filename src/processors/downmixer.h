#pragma once

#include "processor.h"

namespace nldproc {

    typedef unsigned int downmix_mode;
    
    const downmix_mode DOWNMIX_HALF_AMP = 0;
    const downmix_mode DOWNMIX_NEG6_DB = 1;
    const downmix_mode DOWNMIX_SQRT2_2 = 2;

    class downmixer : public processor {
        public:
            downmixer();
            downmixer(downmix_mode mode);
            virtual void process(stereo_buffer input, stereo_buffer output );
        private:
            double factor;
    };
}
