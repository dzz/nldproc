#include "whitenoise.h"
#include "environment.h"
#include "processor.h"

#include <iostream>
#include <random>

namespace nldproc {

    static std::random_device rd;
    static std::mt19937 gen(rd()); 
    static std::uniform_real_distribution<> dist(-1,1);

    void whitenoise::generate(buffer_chunksize samples, single_channel channel) {
        for(sample_index i=0; i<samples;++i) {
            channel[i] = dist(gen);
        }
    }
}
