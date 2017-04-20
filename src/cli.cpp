#include <iostream>
#include <random>
#include <algorithm>

#include "test_signals/whitenoise.h"
#include "test_signals/sine.h"
#include "test_signals/diracs.h"

#include "utils/volume.h"
#include "utils/file.h"

#include "pipe.h"
#include "environment.h"

#include "processors/processors.h"

#include "build.h"
#include "tests.h"

#include "ring_buf.h"

using namespace nldproc;

void print_banner() {
    std::cout<<"nldproc (build "<<NLDPROC_BUILDNUM << ")\n\n";
    std::cout<<"running test: "<< NLDPROC_TOSTRING(NLDPROC_CURRENT_TEST)<< "\n" << "-=-=-=-=-=-=-=-=-=-=-=" << "\n";
}

void verify_ring_buf() {
    ring_buf rb( 6 );

    double input[13]= { 1,2,3,4,5,6,7,8,9,10,11,12,13 };
    double output[13];

    rb.insert( input, 6 );
    rb.retrieve( output, 6 );

    for( int i=0; i<6; ++i) {
        std::cout<< input[i] <<"," << output[i] << "\n";
    }

    for( int i=6; i<13; ++i) {
        rb.insert( &input[i], 1 );
        rb.retrieve( &output[i], 1 );
        std::cout<< input[i] <<"," << output[i] << "\n";
    }
}

int main() {
    print_banner();
    verify_ring_buf();
//    return NLDPROC_CURRENT_TEST();
}
