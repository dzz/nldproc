#pragma once
#include "processor.h"

namespace nldproc {
    class integrator : public processor {
        public:
            integrator(time_seconds time);
        private:
            virtual void process_channel( channel_index channel, single_channel input, single_channel output );
            double i[2];
            double g;
    };
}

