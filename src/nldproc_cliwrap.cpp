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

using namespace nldproc;

void print_banner() {
    std::cout<<"nldproc (build "<<NLDPROC_BUILDNUM << ")\n\n";
    std::cout<<"running test: "<< NLDPROC_TOSTRING(NLDPROC_CURRENT_TEST)<< "\n" << "-=-=-=-=-=-=-=-=-=-=-=" << "\n";
}

int main() {
    print_banner();
    return NLDPROC_CURRENT_TEST();
}

int main_() {

    print_banner();

    os_factor       oversampling = 256;
    pipe            test_pipe;
    waveshaper      test_waveshaper;
    clean_gain      test_gain;
    shaped_noise    test_shaped_lf_noise( lf_noise );  
    shaped_noise    test_shaped_hf_noise( hf_noise );  
    add_buffers     test_add_buffers;

    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer();

    sine::fill_buffer_sweep(40,13000, master_buffer);

    test_pipe.assign_ptr_buffer( alias_list { "buffer:master" }, master_buffer );

    test_pipe.create_buffer( alias_list { "buffer:dithering_noise" } );
    test_pipe.create_oversampled_buffer( alias_list { "buffer(os):waveshaper" }, oversampling );
    test_pipe.create_oversampler("oversampler", oversampling, 10000);
    test_pipe.create_downsampler("downsampler", oversampling, 10000);

    test_pipe.map_processor(&test_gain, {"proc:gain" } );
    test_pipe.map_processor(&test_waveshaper, {"proc:waveshaper" } );
    test_pipe.map_processor(&test_shaped_lf_noise, {"proc:shaped_lf_noise"} ); 
    test_pipe.map_processor(&test_shaped_hf_noise, {"proc:shaped_hf_noise"} ); 
    test_pipe.map_processor(&test_add_buffers, {"proc:mix"} ); 

    test_pipe.create_parameter( 
            "param:Dither Volume(dB)", (parameter_dispatches){ 
                {
                    [](double dB) { return volume::db2vol(dB); },
                    test_pipe.get_control( "proc:gain", "control:gainVol" )
                } 
            }
    );

/*
    test_pipe.create_parameter( 
            "param:Volume(vol)", (parameter_dispatches){
                {
                    [](double vol) { return vol; },
                    test_pipe.get_control( "proc:gain", "control:gainVol" )
                }
            } 
    );*/


    test_pipe.set_parameter("param:Dither Volume(dB)", -60 );
    test_pipe.process_with("proc:shaped_hf_noise", "buffer:dithering_noise", "buffer:dithering_noise");
    test_pipe.process_with("proc:gain", "buffer:dithering_noise", "buffer:dithering_noise");
    test_pipe.process_with("proc:mix", "buffer:dithering_noise", "buffer:master" );

    test_pipe.oversample_into("buffer:master", "buffer(os):waveshaper", oversampling, "oversampler" );
    test_pipe.process_with("proc:waveshaper", "buffer(os):waveshaper", "buffer(os):waveshaper" );
    test_pipe.downsample_into("buffer(os):waveshaper","buffer:master", "downsampler");

    test_pipe.set_parameter("param:Dither Volume(dB)", -96 );
    test_pipe.process_with("proc:shaped_lf_noise", "buffer:dithering_noise", "buffer:dithering_noise");
    test_pipe.process_with("proc:gain", "buffer:dithering_noise", "buffer:dithering_noise");
    test_pipe.process_with("proc:mix", "buffer:dithering_noise", "buffer:master" );




    test_pipe.write_buffer("buffer:master", "oversampled.raw",    binary_left  );
    environment::write_to_file( "output.environment" );

    return 0;


    ///////  test_pipe.write_buffer("buffer(os):waveshaper", "oversampled.raw",    binary_left  );
    ///////  environment::write_to_file( "output.environment" );
    ///////  return 0;

    //test_pipe.process_with("proc:waveshaper", "buffer(os):waveshaper", "buffer(os):waveshaper" );


    //test_pipe.process_with("proc:waveshaper", "buffer:master", "buffer:master" );

    //test_pipe.process_with("proc:waveshaper", "buffer(os):waveshaper", "buffer(os):waveshaper" );
    test_pipe.downsample_into("buffer(os):waveshaper","buffer:master", "downsampler");

    // test_pipe.set_parameter("param:Volume(vol)", 1.0 );
    // test_pipe.process_with("proc:gain", "buffer:master", "buffer:master" );



    test_pipe.write_buffer("buffer:master", "output_stereo.raw",    binary_stereo  );
    test_pipe.write_buffer("buffer:master", "output_left.raw",      binary_left );
    test_pipe.write_buffer("buffer:master", "output_right.raw",     binary_right  );

    environment::write_to_file( "output.environment" );
    return 0;
}












/*
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
}*/

