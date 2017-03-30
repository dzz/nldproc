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
    peakfollower    test_peakfollower;
    stereo_buffer   channels;

    channels = test_pipe.create_unmapped_buffer();
    
    whitenoise::generate( environment::get_buffer_chunksize(), channels[0] );
    whitenoise::generate( environment::get_buffer_chunksize(), channels[1] );

    test_pipe.assign_ptr_buffer( std::vector<std::string> { "buffer:input", "buffer:output" }, channels );
    test_pipe.create_buffer( std::vector<std::string> { "buffer:peakfollower" } );

    test_pipe.map_processor( &test_waveshaper, "module:waveshaper" );
    test_pipe.map_processor( &test_peakfollower, "module:peakfollower" );

    test_pipe.process_with( "module:waveshaper", "buffer:input", "buffer:output" );
    test_pipe.process_with( "module:peakfollower", "buffer:output", "buffer:peakfollower" );

    dump_buffer(channels);
    dump_buffer( test_pipe.get_mapped_buffer("buffer:peakfollower"));

}

