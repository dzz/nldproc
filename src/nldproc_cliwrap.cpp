#include <iostream>
#include <random>
#include <algorithm>

#include "whitenoise.h"
#include "waveshaper.h"
#include "volume.h"
#include "peakfollower.h"
#include "pipe.h"
#include "environment.h"
#include "upmixer.h"

using namespace nldproc;


int main() {

    pipe            test_pipe;
    waveshaper      test_waveshaper;
    peakfollower    test_peakfollower;
    upmixer         test_upmixer;

    stereo_buffer   channels;

    channels = test_pipe.create_unmapped_buffer();

    whitenoise::generate( environment::get_buffer_chunksize(), channels[0] );
    whitenoise::generate( environment::get_buffer_chunksize(), channels[1] );

    test_pipe.assign_ptr_buffer( std::vector<std::string> { "buffer:input", "buffer:output" }, channels );
    test_pipe.create_buffer( std::vector<std::string> { "buffer:peakfollower", "buffer:upmixed" } );

    test_pipe.map_processor( &test_waveshaper,      "module:waveshaper" );
    test_pipe.map_processor( &test_peakfollower,    "module:peakfollower" );
    test_pipe.map_processor( &test_upmixer,         "module:upmixer" );

    test_pipe.process_with( "module:waveshaper", "buffer:input", "buffer:output" );
    test_pipe.process_with( "module:peakfollower", "buffer:output", "buffer:peakfollower" );

    test_pipe.process_with( "module:upmixer", "buffer:peakfollower", "buffer:upmixed");

    test_pipe.dump_buffer( "buffer:upmixed" );
}

