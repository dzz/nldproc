#pragma once
#include "controls.h"
#include "processor.h"

namespace nldproc {

    class tanh_gain : public processor {
        public:
            tanh_gain();
        private:
            virtual void process_channel( channel_index channel, single_channel input, single_channel output );
            control*    gainControl;
    };
}

