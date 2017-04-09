#pragma once

#include "environment.h"
#include "processor.h"


namespace nldproc {
    namespace file {
        void unsafe_fill_from_file( filename raw_file, stereo_buffer target );
    }
}
