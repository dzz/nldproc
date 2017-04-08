#pragma once
#include "processor.h"

namespace nldproc {
    class add_buffers : public processor {
        private:
            virtual void process(stereo_buffer input, stereo_buffer output);
    };
}

