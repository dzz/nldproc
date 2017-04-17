#include "environment.h"
#include "processor.h"
#include "controls.h"

#include <cmath>
#include <iostream>

namespace nldproc {


    void processor::process(stereo_buffer input, stereo_buffer output) {
        for( channel_index idx = 0; idx<2; ++idx) {
            this->process_channel(idx, input[idx],output[idx]);
        }
    }

    latency_samples processor::get_latency() {
        return 0;
    }

    void processor::calibrate() {

    }

    control* processor::get_control( control_name name ) {
        return &this->controls[name];
    }

    control* processor::create_control( control_name name, time_ms smooth_time, control_value value ) {

        control control;

        control.impulse =   value;
        control.state   =   value;
        control.filter_coef = pow( 0.5, 1.0/ ( (smooth_time/2) * environment::get_samplerate() ) );
        control.inv_filter_coef = 1 - control.filter_coef;

        this->controls[name] = control;
        
        //std::cout<<"created control :"<<&this->controls[name]<<"\n";
        //std::cout<<"with filter coef :"<<this->controls[name].filter_coef<<"\n";

        return &this->controls[name];
    }

    double processor::pump_control( control* control ) {

        //std::cout<<"pumping control :"<<control<<"\n";
        //std::cout<<"applied impulse :"<<control->impulse<<"\n";
        control->state = ( control->impulse * control->inv_filter_coef ) + ( control->state * control->filter_coef );
        //std::cout<<"resulting state :"<<control->state<<"\n";

        return control->impulse;
    }

    processor::~processor() {

    }
}
