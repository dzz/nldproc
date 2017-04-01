#pragma once

#include "controls.h"

#include <string>
#include <unordered_map>

namespace nldproc {

    typedef double**     stereo_buffer;
    typedef double*      single_channel;
    typedef unsigned int channel_index;
    typedef double*      sample_addr;

    typedef std::string  control_name;
    typedef unordered_map< control_name, control> controls;

    typedef double       time_ms;
    typedef double       control_value;
          
    class processor {
        public:
            processor();
            virtual void process(stereo_buffer input, stereo_buffer output);
            void create_control( control_name name, time_ms smooth_time, control_value value );
        private:
            double pump_control( control_name name );
            virtual void process_channel(channel_index index, single_channel input, single_channel output) {};
            controls controls;
            
    };

}
