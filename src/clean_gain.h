#pragma once
#include "controls.h"
#include "processor.h"

namespace nldproc {

    class clean_gain : public processor {
        private:
            virtual void process_channel( channel_index single_channel );
            control*    gainControl;

}

