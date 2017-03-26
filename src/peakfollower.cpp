#include "peakfollower.h"
#include <cmath>

namespace nldproc {

    peakfollower::peakfollower() {
        this->output = 0.0;
        this->scalar = 0.0;
        this->samplerate = 1.0;
    }

    void peakfollower::set_halflife(double halflife) {
        this->halflife = halflife;
    }

    void peakfollower::set_samplerate(double samplerate) {
        this->samplerate = samplerate;
    }

    void peakfollower::commit() {
        this->scalar = pow(0.5, 1.0/(this->halflife * this->samplerate));
    }

    inline double peakfollower::eval_next(double x) {
        if( x < 0 ) x*=-1;
        if( x > this->output ) {
            this->output = x;
        } 
        return this->output;
    }

    void peakfollower::process(unsigned int samples, double*channel) {
        unsigned int count = 0;
        while(count<samples) {
            double input = channel[count];
            channel[count++] = this->eval_next(input);
        }
    }
}
