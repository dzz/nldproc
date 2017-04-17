#include "environment.h"
#include "processor.h"
#include "volume.h"
#include "amplifier.h"
#include "fast_tanh_gain.h"
#include "tanh_gain.h"
#include "peakfollower.h"
#include "integrator.h"
#include "rms.h"
#include "delay.h"
#include "pipe_macros.h"
#include "sine.h"
#include "sinc_filter.h"

#include <iostream>

namespace nldproc {

static const double input_rms_ms = (1.0/120.0)*1000;
static const double rms_calibration_hz = 110;
static const double rms_calibration_db = -6;
static const double dc_modulation_db = -48;
static const double peakfollower_decay = ((input_rms_ms)/125)* 0.7444; // very arbitrary
static const double prefilter_hz = 3100;

static const unsigned int prefilter_FIR_tapcount = 7;
static const unsigned int prefilter_FIR_middle = 4; // {middle} + 1 + {middle} = {tapcount}


    amplifier::amplifier() {

        environment::register_calibration_req( this );


        unsigned int lookahead_samples = (unsigned int)( (double) environment::get_samplerate() * 0.006 );
        //
        // configure resources
        //
        /////

        SELECT_PIPE( amp_pipe );

        MAKE_PROC( new fast_tanh_gain(), "p.input.preamp" );
        MAKE_PROC( new tanh_gain(), "p.input.nonlinear_gain" );
        MAKE_PROC( new rms(input_rms_ms) , "p.input.rms" );
        MAKE_PROC( new peakfollower( peakfollower_decay) , "p.input.env.detect" );
        MAKE_PROC( new integrator( (input_rms_ms / 1000.0) *0.5 ), "p.input.env.integrator" );
        MAKE_PROC( new sinc_filter( 17, prefilter_hz / environment::get_samplerate() , SINC_LOWPASS ), "p.input.prefilter" );
        MAKE_PROC( new integrator( 0.2 ), "p.dc_modulator.integrator" );
        MAKE_PROC( new delay( lookahead_samples ), "p.input.lookahead_delay" );

        BUF_ALLOC( { "b.dc_modulator" } );
        BUF_ALLOC( { "b.raw_rms" } );
        BUF_ALLOC( { "b.peak_envelope" } );
        BUF_ALLOC( { "b.dist" } );
        BUF_ALLOC( { "b.hf" } );

        std::cout<<"LAHEAD:"<<lookahead_samples<<"\n";
        latency = prefilter_FIR_middle + lookahead_samples; // center of prefilter
    }


    void amplifier::process(stereo_buffer input, stereo_buffer output ) {

        std::cout<<"PROCESS OF AMPLIFIER\n";
        //
        // simulate some analog
        //
        /////

        SELECT_PIPE( amp_pipe );

        BUF_MAP( { "b.in", "b.in(dc_mod)"  }, input );
        BUF_MAP( { "b.out" }, output );

        BUF_GAIN_DB( "b.in", -6 ); //test value
        PROC_IP( "p.input.preamp", "b.in" );

        PROC( "p.input.rms", "b.in", "b.dc_modulator" );
        BUF_CP( "b.dc_modulator", "b.raw_rms" ); 
        PROC_IP( "p.dc_modulator.integrator", "b.dc_modulator");
        BUF_GAIN_DB( "b.dc_modulator", 36 );


        PROC( "p.input.env.detect", "b.in", "b.peak_envelope" );
        BUF_DITHER( "b.peak_envelope", DB2VOL(-83) );
                                                

        BUF_UPMIX("b.dc_modulator");
        //BUF_DITHER("b.dc_modulator", DB2VOL(-96) );

        BUF_FMUL( "b.dc_modulator", rms_to_calibration_hz ); 
        BUF_ADD_INTO( "b.in", "b.dc_modulator", "b.in(dc_mod)");
        BUF_DIFF("b.peak_envelope","b.raw_rms");

        PROC_IP("p.input.env.integrator", "b.peak_envelope" );
        BUF_GAIN_DB("b.peak_envelope", 7 );

        BUF_GAIN_DB( "b.in(dc_mod)", 7.0 );

        PROC_IP( "p.input.lookahead_delay", "b.in(dc_mod)");
        BUF_CP( "b.in", "b.hf" );
        PROC_IP( "p.input.prefilter", "b.in(dc_mod)" ); 
        BUF_DIFF("b.hf", "b.in(dc_mod)");

        PROC( "p.input.nonlinear_gain", "b.in(dc_mod)", "b.dist" );
        BUF_GAIN_DB( "b.peak_envelope", -2 );
        BUF_XFADE_INTO( "b.dist", "b.in(dc_mod)", "b.out", "b.peak_envelope");

        BUF_ADD_INTO("b.hf","b.out", "b.out");
        BUF_GAIN_DB("b.out",-7);

        //BUF_CP("b.peak_envelope","b.out");
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
        MAKE_PROC( new rms( input_rms_ms ), "p.input.rms");
        PROC_IP( "p.input.rms", "b.rms_calibrator" );

        BUF_MAX( "b.rms_calibrator", rms_to_calibration_hz );
        
        std::cout<<"RMS MAX "<<rms_to_calibration_hz<<"\n";

        INVERT( rms_to_calibration_hz );
        FMUL( rms_to_calibration_hz, DB2VOL( dc_modulation_db ) );

        std::cout<<"processor:"<<this<<" calibrated rms to sine @"<<rms_calibration_hz<<" dB:"<<rms_calibration_db<<" to "<<rms_to_calibration_hz<<"\n";
    }

    pipe* amplifier::get_amp_pipe() {
        return &this->amp_pipe;
    }

}


