#include "environment.h"
#include "processor.h"
#include "volume.h"
#include "fast_tanh_gain.h"

#include <cmath>

namespace nldproc {

    inline double fast_tanh(double x)
    {
    	x = exp(x + x);
    	return (x - 1) / (x + 1);
    }

    constexpr double pi() { return std::atan(1)*4; }

    fast_tanh_gain::fast_tanh_gain() {
        this->gainControl = this->create_control( (control_name)"control:gainVol", (time_ms)4.0, (control_value)1.0 );
    }

    void fast_tanh_gain::process_channel(channel_index index, single_channel input, single_channel output ) {

        double              gainVol;
        sample_index        position        = 0;
        sample_index        total_samples   = environment::get_buffer_chunksize();
        sample_addr         cur_sample      = nullptr;

        while(position < total_samples) {
            gainVol = this->pump_control( this->gainControl );
            output[position] = fast_tanh(pi()*input[position++] * gainVol);
        }
    }
}


