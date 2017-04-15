#include "environment.h"
#include "processor.h"
#include "volume.h"
#include "amplifier.h"
#include "fast_tanh_gain.h"
#include "rms.h"
#include "delay.h"
#include "pipe_macros.h"
#include "sine.h"
#include <iostream>

namespace nldproc {

static const double input_rms_ms = 50;
static const double rms_calibration_hz = 440;
static const double rms_calibration_db = -6;

    
    void amplifier::calibrate() {

        pipe calibration_pipe;

        SELECT_PIPE( calibration_pipe );
        BUF_ALLOC( { "b.rms_calibrator" } );

        SINE_FILL( rms_calibration_hz, "b.rms_calibrator" );
        BUF_GAIN_DB( "b.rms_calibrator", rms_calibration_db );
        MAKE_PROC( new rms( input_rms_ms ), "p.rms");
        PROC_IP( "p.rms", "b.rms_calibrator" );

        rms_to_calibration_hz = BUF_MAX( "b.rms_calibrator" );
        
        std::cout<<"processor:"<<this<<" calibrated rms to sine @"<<rms_calibration_hz<<" dB:"<<rms_calibration_db<<" to "<<rms_to_calibration_hz<<"\n";
    }

    amplifier::amplifier() {

        environment::register_calibration_req( this );

        SELECT_PIPE( amp_pipe );
        BUF_ALLOC( { "b.rms_synched_input" } );
        MAKE_PROC( new fast_tanh_gain(), "p.input.gain" );
        MAKE_PROC( new rms(input_rms_ms) , "p.input.rms" );

        rms* RMS = (rms*)GET_PROC("p.input.rms");

        MAKE_PROC( new delay( RMS->get_filter_size() ), "p.input.rms_synch_delay");

        latency = RMS->get_latency();
    }

    latency_samples amplifier::get_latency() {
        return latency;
    }

    void amplifier::process(stereo_buffer input, stereo_buffer output ) {

        SELECT_PIPE( amp_pipe );

        BUF_MAP( { "b.input" }, input );
        BUF_MAP( { "b.output" }, output );

        //PROC    ( "p.input.gain", "b.input", "b.rms_synched_input" );
        //PROC_IP ( "p.input.rms_synch_delay", "b.rms_synched_input" );

        PROC ( "p.input.rms_synch_delay", "b.input", "b.output");

        //BUF_CP( "b.rms_synched_input", "b.output" );
    }

}


