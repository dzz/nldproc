#include <iostream>
#include <random>

#include "DspFilters/Filter.h"
#include "DspFilters/RBJ.h"

#include "whitenoise.h"

int main() {

    const int numSamps = 256;
    Dsp::SimpleFilter <Dsp::RBJ::LowPass, 1> f; 
    f.setup(44100, 1000, 1); //this works, yay! external library loaded

    double* noise = whitenoise::generate(numSamps); 

    for(int i=0; i<numSamps;++i) {
        std::cout<<i<<","<<noise[i]<<"\n";
    }

    double* channels[1] = { noise };
    f.process(numSamps,channels); 

    for(int i=0; i<numSamps;++i) {
        std::cout<<numSamps+i<<","<<noise[i]<<"\n";
    }

    delete noise;
}
