#pragma once

#include "environment.h"
#include "processor.h"
#include "pipe.h"

namespace nldproc {
    class whitenoise {
        public:
            static void generate(buffer_chunksize samples, single_channel channel );
            static void fill_buffer(stereo_buffer buffer);
    };
}


