#pragma once

#include "test_signal.h"
#include "environment.h"
#include "processor.h"
#include "pipe.h"

namespace nldproc {

    class whitenoise : public test_signal {
        public:
            static void generate(buffer_chunksize samples, single_channel channel );
            static void fill_buffer(stereo_buffer buffer);
        private:
    };
}


