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
#include "downmixer.h"
#include "clean_gain.h"

using namespace nldproc;

int main() {

 
    /////////////
    // define test pipe

    pipe            test_pipe; 

    /////////////
    // make some processor instances and assign them names on the pipe

    waveshaper      test_waveshaper;
    peakfollower    test_peakfollower;
    upmixer         test_upmixer;
    downmixer       test_downmixer;
    clean_gain      test_clean_gain;




    test_pipe.map_processor( &test_waveshaper,      "module:waveshaper" );
    test_pipe.map_processor( &test_peakfollower,    "module:peakfollower" );
    test_pipe.map_processor( &test_upmixer,         "module:upmixer" );
    test_pipe.map_processor( &test_downmixer,       "module:downmixer" );

    /////////////
    // define a stereo buffer for our test signal, memory will be managed by the
    // pipe. 

    stereo_buffer channels = test_pipe.create_unmapped_buffer();

    /////////////
    // generate stereo sample signal

    whitenoise::generate( environment::get_buffer_chunksize(), channels[0] );
    whitenoise::generate( environment::get_buffer_chunksize(), channels[1] );

    
    /////////////
    // assign aliases to our test signal. normally this would be an address given 
    // to us by the audio driver or plugin host with the expectation of being filled in place

    test_pipe.assign_ptr_buffer( alias_list { "buffer:input", "buffer:output" }, channels  );

    
    /////////////
    // create buffers. a single buffer can have multiple aliases.

    test_pipe.create_buffer( alias_list { "buffer:peakfollower",   "buffer:upmixed"    } );
    test_pipe.create_buffer( alias_list { "buffer:downmixed"                           } );


    /////////////
    // create a name parameter which will dispatch to one target

    test_pipe.create_parameter( {
        "parameter:Volume (dB)",
        {
            [](x) { return volume::db2vol(x); },
            test_pipe.get_control("module:clean_gain", "control:gainVol")
        },
        0.0
    } );

    test_pipe.process_with( "module:downmixer",     "buffer:input",         "buffer:downmixed" );
    test_pipe.process_with( "module:waveshaper",    "buffer:input",         "buffer:output" );
    test_pipe.process_with( "module:peakfollower",  "buffer:output",        "buffer:peakfollower" );
    test_pipe.process_with( "module:upmixer",       "buffer:peakfollower",  "buffer:upmixed");

    test_pipe.dump_buffer( "buffer:downmixed" );
}

