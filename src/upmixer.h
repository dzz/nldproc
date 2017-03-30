#pragma once
#include "processor.h"

namespace nldproc {

    class upmixer : public processor {
        public:
            virtual void process(stereo_buffer input, stereo_buffer output );
    };
}
