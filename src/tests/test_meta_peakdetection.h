int test_meta_peakdetection() {

    environment::configure_test_environment( (frequency_hz)44100, (sample_count)44100*10 ); 

    pipe            test_pipe;          
    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer(); 
    rms             test_rms(15);
    peakfollower    test_peakfollower(0.5);
    derivative      test_derivative;

    file::unsafe_fill_from_file(  NLDPROC_TEST_RAW_AUDIO_FILE, master_buffer );
    test_pipe.assign_ptr_buffer( {"buf:master"}, master_buffer );

    test_pipe.create_buffer( { "buf:rms" } );
    test_pipe.create_buffer( { "buf:pf" } );

    test_pipe.map_processor( &test_rms, {"proc:rms"} );
    test_pipe.map_processor( &test_peakfollower, {"proc:pf"} );
    test_pipe.map_processor( &test_derivative, {"proc:derive"} );

    test::write_input_signal_test_data( &test_pipe, "buf:master");

    test_pipe.process_with( "proc:rms", "buf:master", "buf:rms" );
    test_pipe.process_with( "proc:pf", "buf:master", "buf:pf" );
    test_pipe.difference_into( "buf:pf", "buf:rms", "buf:master");
    test_pipe.process_with_inplace("proc:derive", "buf:master");


    // write test report info to file 
    test::write_mono_test_data( &test_pipe, "buf:master", NLDPROC_FFT_LIMITS(10,20000) );

    return NLDPROC_TEST_SUCCESS;
}
