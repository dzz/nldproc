#pragma once

namespace nldproc {

    class peakfollower {

        public:
            peakfollower();
            void set_halflife(double halflife);
            void set_samplerate(double samplerate);
            void commit();
            void process(unsigned int samples, double* channels);
        private:

            inline double eval_next(double x);
            double output;
            double scalar;
            double halflife;
            double samplerate;
    };
}
