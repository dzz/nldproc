#pragma once
#include "controls.h"
#include "processor.h"

namespace nldproc {
    class clean_gain : public processor {
        public:
            clean_gain();
        private:
            virtual void process_channel( channel_index channel, single_channel input, single_channel output );
            control*    gainControl;
    };
}

