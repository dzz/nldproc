int test_peakfollower() {

    environment::configure_test_environment( (frequency_hz)44100, (sample_count)44100*10 ); 

    pipe            test_pipe;          
    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer(); 
    peakfollower    test_peakfollower(0.2); 

    file::unsafe_fill_from_file(  NLDPROC_TEST_RAW_AUDIO_FILE, master_buffer );
    test_pipe.assign_ptr_buffer( {"buf:master"}, master_buffer );
    test_pipe.map_processor( &test_peakfollower, {"proc:peakfollower"} );
    test::write_input_signal_test_data( &test_pipe, "buf:master");
    test_pipe.process_with_inplace( "proc:peakfollower", "buf:master" );

    // write test report info to file 
    test::write_mono_test_data( &test_pipe, "buf:master", NLDPROC_FFT_LIMITS(10,20000) );

    return NLDPROC_TEST_SUCCESS;
}
