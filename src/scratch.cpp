//Sample interface for buffer routing code
//
//
//   Building the following DSP topology
//
//   () indicate buffer id
//
//            
//
//       [ audio input(0) ]
//                   |
//                  / \
//                 /   \
//          [ LPF (1) ] [ peakfollower (2) ]
//                |    /
//                |   /
//                |  /
//                | /
//             [ multiply (1) ]
//                |
//                |
//             [ waveshaping distortion (1) ]
//                |
//                |
//             [ audio output(0) ]
//         
//
//


void plugin::plugin() {
    this->buffers = buffers();

    //the individual DSP processors to use
    this->lpf_filter    = new lpf_filter();
    this->peakfollower  = new peakfollower();
    this->waveshaper    = new waveshaper();

    
    //the chunksize based on the audio drivers requested buffer size
    this->buffers.set_chunksize(1024);

    //create an input which will be mapped to the audio 
    //audio driver's requested memory location
    this->buffers.create_ptrinput_buffer("input");


    //create the LPF buffer
    this->buffers.create_memory_buffer("lpf");

    //create the Peakfollower buffer
    this->buffers.create_memory_buffer("peakfollower");

    //create alias buffers for semantic naming, reusing the same
    //buffer to process in place
    this->buffers.create_alias_buffer_from_to("lpf", "lpf*peakfollower");
    this->buffers.create_alias_buffer_from_to("lpf", "lpf*peakfollower (distorted)");

    //create an alias buffer from output to input, as the audio driver
    //wants results in the same memory location requested in 'process'
    this->buffers.create_alisa_buffer_from_to("input", "output");

}

void plugin::process(double* channels) {

    //arm the input buffer, which also arms output
    this->buffers.arm_ptrinput_buffer("input", channels );

    //process "input" with the LPF putting results in "lpf"
    this->buffers.process_to_with_from("lpf",           this->lpf_filter,   "input" );

    //process "input" with the peakfollower, putting results in "peakfollower"
    this->buffers.process_to_with_from("peakfollower",  this->peakfollower, "input" );

    //multiply "peakfollower" by "lpf*peakfollower" putting results in "lpf*peakfollower",
    //
    // -- notice that we're reusing the "lpf" buffer here because it's an alias and we
    //    don't need to preserve the values from the "lpf" buffer
    this->buffers.multiply_right("peakfollower", "lpf*peakfollower");

    //process "lpf*peakfollower (distorted)" in place with the waveshaper
    //
    // -- again, we're really using the "lpf*peakfollower" buffer which itself
    //    is just the "lpf" buffer
    this->buffers.process_in_place_with("lpf*peakfollower (distorted)", waveshaper );

    //copy the memory in "lpf*peakfollower (distorted)" into output, which is
    //an alias of "output" which is the double* chanels pointer passed into this
    //function
    this->buffers.clone_from_to("lpf*peakfollower (distorted)","output");

}
