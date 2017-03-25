#include <iostream>
#include <random>
#include <algorithm>

#include "DspFilters/Filter.h"
#include "DspFilters/RBJ.h"

#include "whitenoise.h"
#include "waveshaper.h"

using namespace nldproc;

int main() {

    waveshaper ws;
    
    ws.add_point(-2.0,-2.0,1.0);
    ws.add_point(0.0,0.0,0.0);
    ws.add_point(2.0,2.0,-1.0);

    ws.commit();

/*
    std::for_each( points.begin(), points.end(), []( auto point ) {
        std::cout<<"x="<<point.x<<"\n";
    });
*/

    const unsigned int samples = (96000*4);
    double* channels[2];

    channels[0] = whitenoise::generate(samples);
    channels[1] = whitenoise::generate(samples);

    ws.process(samples,channels);

    for(auto idx = 0; idx<(96000*4);++idx) {
        std::cout<<channels[idx]<<"\n";
    }
    

    delete channels[0];
    delete channels[1];
     
    
/*
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

    delete noise;*/
}
