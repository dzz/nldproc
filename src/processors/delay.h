#pragma once
#include "processor.h"
#include "fir.h"

namespace nldproc {
    class delay : public fir {
        public:
            delay( tapcount length );
    };
}

