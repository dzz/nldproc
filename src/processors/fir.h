#pragma once
#include "processor.h"
#include "environment.h"
#include "ring_buf.h"

namespace nldproc {

    typedef unsigned int tapcount;
    typedef double* coefficients;
    typedef double coefficient;
    typedef ring_buf delay_line;

    class fir : public processor {
        public:
            fir( tapcount size, coefficients spec );
            ~fir();
        private:
            tapcount filter_size;
            delay_line* history[2];
            double* tmp;

            coefficients filter;
            virtual void process_channel( channel_index channel, single_channel input, single_channel output );
        protected:
            fir();
            void configure( tapcount size, coefficients spec );
    };
}

