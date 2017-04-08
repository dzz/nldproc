#pragma once
#include "processor.h"

namespace nldproc {
    class clone_buffer : public processor {
        public:
            clone_buffer();
        private:
            virtual void process(stereo_buffer input, stereo_buffer output);
    };
}

