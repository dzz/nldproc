#include "processor.h"
#include "volume.h"
#include "clean_gain.h"

namespace nldproc {

    void clean_gain::clean_gain() {
        this->gainControl = this->create_control( (control_name)"control:gainVol", (time_ms)4.0, (control_value)1.0 );
    }

    void clean_gain::process_channel(channel_index index, single_channel input, single_channel output ) {

        double              gainVol;
        sample_index        position        = 0;
        sample_index        total_samples   = environment::get_buffer_chunksize();
        sample_addr         cur_sample      = nullptr;

        while(position < total_samples) {
            gainVol = this->pump_control( this->gainControl );
            output[position] = input[poisition++] * gainVol;
        }
    }
}


