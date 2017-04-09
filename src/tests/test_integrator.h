#if ( NLDPROC_CURRENT_TEST == test_integrator )

int test_integrator() {

    environment::configure_test_environment( (frequency_hz)44100, (sample_count)44100*5 ); 

    pipe            test_pipe;          
    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer(); 
    integrator      test_integrator;

    file::unsafe_fill_from_file(  NLDPROC_TEST_RAW_AUDIO_FILE, master_buffer );
    test_pipe.assign_ptr_buffer( {"buf:master"}, master_buffer );
    test_pipe.map_processor( &test_integrator, {"proc:integrator"} );
    test_pipe.process_with_inplace( "proc:integrator", "buf:master" );


    // write test report info to file 
    test_pipe.write_buffer( "buf:master", "output/integrator.raw", binary_left );
    environment::write_samplerate_to_file( "output/test.samplerate" );
    environment::write_filename_to_file( "integrator.raw", "output/test.reportfile" );
    environment::write_fft_limits_to_file("output/test.report_fft_lims", (frequency_hz)100, (frequency_hz)20000);

    return NLDPROC_TEST_SUCCESS;
}

#endif
