#include "environment.h"
#include "processor.h"
#include "controls.h"

#include <cmath>

namespace nldproc {

    void processor::process(stereo_buffer input, stereo_buffer output) {
        for( channel_index idx = 0; idx<2; ++idx) {
            this->process_channel(idx, input[idx],output[idx]);
        }
    }

    control* processor::get_control( control_name name ) {
        return &this->controls[name];
    }

    control* processor::create_control( control_name name, time_ms smooth_time, control_value value ) {

        control control;

        control.impulse =   value;
        control.state   =   value;
        control.filter_coef = pow( (smooth_time/2) * environment::get_samplerate() );
        control.inv_filter_coef = 1 - control.filter_coef;

        this->controls[name] = control;
        
        return &control;
    }

    double processor::pump_control( control* control );
        return control->state = ( control->impulse * control->filter_coef ) + ( control->state * control->inv_filter_coef );
    }
}
