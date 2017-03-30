#pragma once

#include "environment.h"
#include "processor.h"

namespace nldproc {
    class whitenoise {
        public:
            static void generate(buffer_chunksize samples, single_channel channel );
    };
}


