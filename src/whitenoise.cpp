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

    void whitenoise::fill_buffer( stereo_buffer channels ) {
        whitenoise::generate( environment::get_buffer_chunksize(), channels[0] );
        whitenoise::generate( environment::get_buffer_chunksize(), channels[1] );
    }
}
