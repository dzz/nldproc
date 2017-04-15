#pragma once
#include "controls.h"
#include "processor.h"

#include "pipe.h"
#include "fast_tanh_gain.h"
#include "rms.h"

namespace nldproc {
    class amplifier : public processor {
        public:
            amplifier();
        private:
            virtual void process(stereo_buffer input, stereo_buffer output);
            control*    gainControl;

            pipe            amp_pipe;
            fast_tanh_gain  gain_stage_1;           
            rms             input_rms;
            
    };
}

