#include "environment.h"
#include "processor.h"
#include "volume.h"
#include "amplifier.h"

namespace nldproc {

    amplifier::amplifier() {
        //this->gainControl = this->create_control( (control_name)"control:gainVol", (time_ms)4.0, (control_value)1.0 );

        amp_pipe.map_processor( &gain_stage_1, "p.gain_stage_1" );
        amp_pipe.map_processor( &input_rms, "p.input_rms" );
    }

    void amplifier::process(stereo_buffer input, stereo_buffer output ) {
        amp_pipe.assign_ptr_buffer( { "b.input" }, input );
        amp_pipe.assign_ptr_buffer( { "b.output" }, output );

        amp_pipe.process_with( "p.gain_stage_1", "b.input", "b.output" );
    }

}


