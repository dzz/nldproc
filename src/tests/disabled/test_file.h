int test_file() {

    environment::configure_test_environment( (frequency_hz)44100, (sample_count)44100*7 ); 

    pipe            test_pipe;          
    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer(); 

    environment::enter_implicit_time(); //start profiler ourselves, not triggering with a process call
    file::unsafe_fill_from_file(  NLDPROC_TEST_RAW_AUDIO_FILE, master_buffer );
    test_pipe.assign_ptr_buffer( {"buf:master"}, master_buffer );

    // write test report info to file 
    test::write_mono_test_data( &test_pipe, "buf:master", NLDPROC_FFT_LIMITS(100,20000) );
    test::write_input_signal_test_data( &test_pipe, "buf:master");

    return NLDPROC_TEST_SUCCESS;
}
