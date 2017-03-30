#include "environment.h"

namespace nldproc {

    samplerate environment::get_samplerate() {
        return 96000;
    }
    
    buffer_chunksize environment::get_buffer_chunksize() {
        return 1024;
    }
}
