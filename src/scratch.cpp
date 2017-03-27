

void plugin::plugin() {
    this->buffers = buffers();

    //the individual DSP processors to use
    this->lpf_filter    = new lpf_filter();
    this->peakfollower  = new peakfollower();
    this->waveshaper    = new waveshaper();

    
    //the chunksize based on the audio drivers requested buffer size
    this->buffers.set_chunksize(1024);

    //create two inputs which will be mapped to pointers
    this->buffers.create_ptrinput_buffer("input");
    this->buffers.create_ptrinput_buffer("output");

    this->buffers.create_memory_buffer("lpf");
    this->buffers.create_alias_buffer_from_to("lpf", "lpf*peakfollower");
    this->buffers.create_alias_buffer_from_to("lpf", "lpf*peakfollower (distorted)");
    this->buffers.create_memory_buffer("peakfollower");
}

void plugin::process(double* channels) {

    this->buffers.arm_ptrinput_buffer("input", channels );
    this->buffers.arm_ptrinput_buffer("output", channels );
    this->buffers.process_to_with_from("lpf", lpf_filter,  "input" );
    this->buffers.process_to_with_from("peakfollower", peakfollower, "input" );
    this->buffers.multiply_right("peakfollower", "lpf*peakfollower");
    this->buffers.process_in_place_with("lpf*peakfollower (distorted)", waveshaper );
    this->buffers.clone_from_to("lpf*peakfollower (distorted)","output");

}
