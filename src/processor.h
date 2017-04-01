#pragma once

#include "controls.h"

#include <string>
#include <unordered_map>

namespace nldproc {

    typedef double**     stereo_buffer;
    typedef double*      single_channel;
    typedef unsigned int channel_index;
    typedef double*      sample_addr;

    typedef std::unordered_map< control_name, control> control_collection;

    typedef double       time_ms;
          
    class processor {
        public:
            virtual void process(stereo_buffer input, stereo_buffer output);
            control* create_control( control_name name, time_ms smooth_time, control_value value );
            control* get_control( control_name name );
        private:
            virtual void process_channel(channel_index index, single_channel input, single_channel output) {};
            control_collection controls;
        protected:
            double pump_control( control* control );
            
    };

}
