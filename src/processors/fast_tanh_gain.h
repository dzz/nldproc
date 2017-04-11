#pragma once
#include "controls.h"
#include "processor.h"

namespace nldproc {

    class fast_tanh_gain : public processor {
        public:
            fast_tanh_gain();
        private:
            virtual void process_channel( channel_index channel, single_channel input, single_channel output );
            control*    gainControl;
    };
}

