#pragma once
#include "processor.h"

namespace nldproc {

    class peakfollower : public processor {

        public:
            peakfollower(time_seconds decay_halflife);
            void set_halflife(double halflife);
            void set_samplerate(double samplerate);
            void commit();
            virtual void process_channel(channel_index index, single_channel input, single_channel output);
        private:

            virtual latency_samples get_latency();

            inline double eval_next(double x);
            double output;
            double scalar;
            double halflife;
            double samplerate;
            unsigned int frame;
    };
}
