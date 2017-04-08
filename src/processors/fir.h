#pragma once
#include "processor.h"
#include "environment.h"

namespace nldproc {

    typedef unsigned int tapcount;
    typedef double* coefficients;
    typedef double coefficient;
    typedef double* delay_line;

    class fir : public processor {
        public:
            fir( tapcount size, coefficients spec );
            ~fir();
        private:
            tapcount filter_size;
            delay_line inputs[2];
            coefficients filter;
            virtual void process_channel( channel_index channel, single_channel input, single_channel output );
    };
}

