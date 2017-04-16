#include "environment.h"
#include "processor.h"
#include "volume.h"
#include "tanh_gain.h"

#include <cmath>

namespace nldproc {

    inline double pi() { return std::atan(1)*4; }

    tanh_gain::tanh_gain() {
        this->gainControl = this->create_control( (control_name)"control:gainVol", (time_ms)4.0, (control_value)1.0 );
    }

    void tanh_gain::process_channel(channel_index index, single_channel input, single_channel output ) {

        double              gainVol;
        sample_index        position        = 0;
        sample_index        total_samples   = environment::get_buffer_chunksize();
        sample_addr         cur_sample      = nullptr;

        while(position < total_samples) {
            gainVol = this->pump_control( this->gainControl );
            output[position] = std::tanh(pi()*input[position++] * gainVol);
        }
    }
}


