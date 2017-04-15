#include "delay.h"
#include "environment.h"
#include "processor.h"

namespace nldproc {
    delay::delay( tapcount length ) {
        double delay_spec[length];
        for(sample_index idx=0; idx< length;++idx) {
            delay_spec[idx] = 0.0;
        }
        delay_spec[ length -1 ] = 1.0;

        this->configure( length, delay_spec );
    }
        
}
