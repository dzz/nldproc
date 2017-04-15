#include "environment.h"
#include "processor.h"
#include "volume.h"
#include "amplifier.h"
#include "fast_tanh_gain.h"
#include "peakfollower.h"
#include "rms.h"
#include "delay.h"
#include "pipe_macros.h"
#include "sine.h"
#include <iostream>

namespace nldproc {

static const double input_rms_ms = (1.0/30.0)*1000;
static const double rms_calibration_hz = 440;
static const double rms_calibration_db = -6;
static const double dc_modulation_db = -48;
static const double peakfollower_decay = ((input_rms_ms)/1000)* 0.7444; // very arbitrary
    

    amplifier::amplifier() {

        environment::register_calibration_req( this );

        //
        // configure resources
        //
        /////

        SELECT_PIPE( amp_pipe );

        MAKE_PROC( new fast_tanh_gain(), "p.input.nonlinear_gain" );
        MAKE_PROC( new rms(input_rms_ms) , "p.input.rms" );
        MAKE_PROC( new peakfollower( peakfollower_decay) , "p.input.env_detect" );

        BUF_ALLOC( { "b.dc_modulator" } );
        BUF_ALLOC( { "b.raw_rms" } );
        BUF_ALLOC( { "b.peak_envelope" } );
        BUF_ALLOC( { "b.dist" } );

        latency = 0;
    }


    void amplifier::process(stereo_buffer input, stereo_buffer output ) {

        //
        // simulate some analog
        //
        /////

        SELECT_PIPE( amp_pipe );

        BUF_MAP( { "b.in", "b.in(dc_mod)"  }, input );
        BUF_MAP( { "b.out" }, output );

        PROC( "p.input.rms", "b.in", "b.dc_modulator" );
        BUF_CP( "b.dc_modulator", "b.raw_rms" ); 
        BUF_SQUARE( "b.raw_rms" );

        PROC( "p.input.env_detect", "b.in", "b.peak_envelope" );
        BUF_SQUARE( "b.peak_envelope" );
        BUF_DITHER( "b.peak_envelope", DB2VOL(-83) );

        BUF_UPMIX("b.dc_modulator");
        BUF_DITHER("b.dc_modulator", DB2VOL(-96) );

        BUF_FMUL( "b.dc_modulator", rms_to_calibration_hz ); 
        BUF_ADD_INTO( "b.in", "b.dc_modulator", "b.in(dc_mod)");
        BUF_DIFF("b.peak_envelope","b.raw_rms");

        PROC( "p.input.nonlinear_gain", "b.in(dc_mod)", "b.dist" );
        BUF_XFADE_INTO( "b.dist", "b.in(dc_mod)", "b.out", "b.peak_envelope");

        BUF_CP("b.peak_envelope","b.out");
    }


    latency_samples amplifier::get_latency() {
        return latency;
    }


    void amplifier::calibrate() {

        pipe calibration_pipe;

        SELECT_PIPE( calibration_pipe );
        BUF_ALLOC( { "b.rms_calibrator" } );

        SINE_FILL( rms_calibration_hz, "b.rms_calibrator" );
        BUF_GAIN_DB( "b.rms_calibrator", rms_calibration_db );
        MAKE_PROC( new rms( input_rms_ms ), "p.rms");
        PROC_IP( "p.rms", "b.rms_calibrator" );

        BUF_MAX( "b.rms_calibrator", rms_to_calibration_hz );
        
        std::cout<<"RMS MAX "<<rms_to_calibration_hz<<"\n";

        INVERT( rms_to_calibration_hz );
        FMUL( rms_to_calibration_hz, DB2VOL( dc_modulation_db ) );

        std::cout<<"processor:"<<this<<" calibrated rms to sine @"<<rms_calibration_hz<<" dB:"<<rms_calibration_db<<" to "<<rms_to_calibration_hz<<"\n";
    }

}


