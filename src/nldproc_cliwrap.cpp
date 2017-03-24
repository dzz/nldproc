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
    
    ws.add_point(0.5,1.0,0.0);
    ws.add_point(-0.5,1.0,0.0);
    auto last_id = ws.add_point(-0.9,1.0,0.0);

    ws.del_point(last_id);
    auto points = ws.get_copyof_points();

    std::for_each( points.begin(), points.end(), []( auto point ) {
        std::cout<<"x="<<point.x<<"\n";
    });

     
    
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
