int test_delay() {

    environment::configure_test_environment( (frequency_hz)1, (sample_count)16);

    pipe            test_pipe;          
    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer(); 
    delay       test_delay(8);

    test_pipe.assign_ptr_buffer( {"buf:master"}, master_buffer );

    sine::fill_range( 0.25, test_pipe.get_mapped_buffer( "buf:master" ), 0, 8 ); 
    test::write_input_signal_test_data( &test_pipe, "buf:master");

    test_pipe.map_processor( &test_delay, {"proc:delay"} );

    test_pipe.process_with_inplace( "proc:delay", "buf:master" );

    // write test report info to file 
    test::write_mono_test_data( &test_pipe, "buf:master", NLDPROC_FFT_LIMITS(10,20000) );

    return NLDPROC_TEST_SUCCESS;
}
