int test_amplifier() {

    environment::configure_test_environment( (frequency_hz)44100, (sample_count)44100*1.5 ); 

    pipe            test_pipe;          
    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer(); 
    amplifier       test_amplifier;


    file::unsafe_fill_from_file(  NLDPROC_TEST_RAW_AUDIO_FILE, master_buffer );
    //sine::fill_buffer_sweep( 10, 3000, master_buffer );

    std::cout<<"SINE SIGNAL\n";
    
    std::cout<<"MAP BUFFER'n";
    test_pipe.assign_ptr_buffer( {"buf:master"}, master_buffer );
    test_pipe.map_processor( &test_amplifier, {"proc:amplifier"} );

    test::write_input_signal_test_data( &test_pipe, "buf:master");
    test_pipe.process_with_inplace( "proc:amplifier", "buf:master" );

    //
    std::cout<<"PROCESSED!\n";
    // write test report info to file - timeshifting
    test::time_shift_forward( &test_pipe, test_amplifier.get_latency(), "buf:master");
    test::write_mono_test_data( &test_pipe, "buf:master", NLDPROC_FFT_LIMITS(10,20000) );
    test::write_additional_buffer( test_amplifier.get_amp_pipe(), "b.peak_envelope" );
    test::write_additional_buffer( test_amplifier.get_amp_pipe(), "b.dc_modulator" );

    return NLDPROC_TEST_SUCCESS;
}
