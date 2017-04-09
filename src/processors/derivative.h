#pragma once
#include "processor.h"

namespace nldproc {
    class derivative : public processor {
        public:
            derivative();
        private:
            virtual void process_channel( channel_index channel, single_channel input, single_channel output );
            double i[2];
    };
}

