#include <iostream>
#include <random>
#include <algorithm>

#include "whitenoise.h"
#include "waveshaper.h"
#include "volume.h"
#include "peakfollower.h"
#include "pipe.h"
#include "environment.h"

using namespace nldproc;

void dump_buffer( stereo_buffer buffer ) {

    for( sample_index idx = 0; idx < environment::get_buffer_chunksize(); ++idx) {
        std::cout<<buffer[0][idx]<<","<<buffer[1][idx]<<"\n";
    }
}

int main() { 

    pipe            test_pipe;
    waveshaper      test_waveshaper;
    stereo_buffer   channels;

    channels = test_pipe.create_unmapped_buffer();
    
    whitenoise::generate( environment::get_buffer_chunksize(), channels[0] );
    whitenoise::generate( environment::get_buffer_chunksize(), channels[1] );

    dump_buffer(channels);

    test_pipe.assign_ptr_buffer( std::vector<std::string> { "input", "output" }, channels );
    test_pipe.map_processor( &test_waveshaper, "waveshaper" );
    test_pipe.process_with( "waveshaper", "input", "output" );

    dump_buffer(channels);

}

