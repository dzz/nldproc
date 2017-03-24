#include "whitenoise.h"
#include <iostream>
#include <random>

namespace nldproc {
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_real_distribution<> dist(-1,1);

    double* whitenoise::generate(int samples) {
        double* noise = new double[samples];
        for(int i=0; i<samples;++i) {
            noise[i] = dist(gen);
        }
        return noise;
    }
}
