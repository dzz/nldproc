#include "peakfollower.h"
#include "processor.h"
#include "environment.h"

#include <cmath>

namespace nldproc {

    peakfollower::peakfollower(time_seconds decay_halflife) {
        this->output = 0.0;
        this->scalar = 0.0;
        this->samplerate = (double)environment::get_samplerate();
        this->set_halflife( decay_halflife );
        this->commit();
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
        //if( x < 0 ) x*=-1;

        if( x > this->output ) {
            this->output = x;
        } else {
            this->output = this->output * this->scalar;
        }
        return this->output;
    }

    void peakfollower::process_channel(channel_index index, single_channel input, single_channel output ) {
        sample_index        position        = 0;
        sample_index        total_samples   = environment::get_buffer_chunksize();
        sample_addr         cur_sample      = nullptr;

        if( index == 0 ) {
            while(position  <   total_samples) {
                cur_sample  = &input[position];

                output[position++] = this->eval_next(*cur_sample);
            }
        }
    }
}
