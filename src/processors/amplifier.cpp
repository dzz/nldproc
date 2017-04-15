#include "environment.h"
#include "processor.h"
#include "volume.h"
#include "amplifier.h"
#include "fast_tanh_gain.h"
#include "rms.h"
#include "delay.h"

namespace nldproc {

static const double input_rms_ms = 50;

#define MAKE_PROC amp_pipe.map_managed_processor
#define GET_PROC amp_pipe.get_processor
#define BUF_MAP amp_pipe.assign_ptr_buffer
#define PROC amp_pipe.process_with
#define PROC_IP amp_pipe.process_with_inplace
#define BUF_ALLOC amp_pipe.create_buffer
#define BUF_CP amp_pipe.copy_into

    
    void amplifier::calibrate() {

    }

    amplifier::amplifier() {

        environment::register_calibration_req( this );

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
        BUF_MAP( { "b.input" }, input );
        BUF_MAP( { "b.output" }, output );

        //PROC    ( "p.input.gain", "b.input", "b.rms_synched_input" );
        //PROC_IP ( "p.input.rms_synch_delay", "b.rms_synched_input" );

        PROC ( "p.input.rms_synch_delay", "b.input", "b.output");

        //BUF_CP( "b.rms_synched_input", "b.output" );
    }

}


