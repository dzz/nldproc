#pragma once

#include "processor.h"

namespace nldproc {
    class downmixer : public processor {
        public:
            virtual void process(stereo_buffer input, stereo_buffer output );
    };
}
