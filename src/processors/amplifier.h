#pragma once
#include "controls.h"
#include "processor.h"
#include "pipe.h"

namespace nldproc {
    class amplifier : public processor {
        public:
            amplifier();
            virtual latency_samples get_latency();
            virtual void calibrate();
        private:
            virtual void process(stereo_buffer input, stereo_buffer output);

            control*    gainControl;

            pipe                amp_pipe;
            latency_samples    latency;
            double rms_to_calibration_hz;
            
    };
}

