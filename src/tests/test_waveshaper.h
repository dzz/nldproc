#if ( NLDPROC_CURRENT_TEST == test_waveshaper )

int test_waveshaper() {

    environment::configure_test_environment( (frequency_hz)44100, (sample_count)44100 ); 

    const os_factor OS_Amount = 7;
    pipe            test_pipe;          
    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer(); 

    sinc_filter     up_filter( 127, 0.4*(1.0/(double)OS_Amount), SINC_LOWPASS ); //0.4/0.46 close to half band
    sinc_filter     down_filter( 127, 0.46*(1.0/(double)OS_Amount), SINC_LOWPASS );
    waveshaper      test_waveshaper;
 
    test_pipe.map_processor( &up_filter,       {"proc:up_filter"  } );
    test_pipe.map_processor( &down_filter,     {"proc:down_filter"} );
    test_pipe.map_processor( &test_waveshaper, {"proc:waveshaper" } );

    test_pipe.assign_ptr_buffer(         {"buf:master"},        master_buffer );
    test_pipe.create_oversampled_buffer( { "buf:oversampled" } , OS_Amount );

    sine::fill_buffer_sweep(15000,40, master_buffer);

    test_pipe.oversample_into( "buf:master", "buf:oversampled", OS_Amount, "" );
    test_pipe.process_with_inplace("proc:up_filter","buf:oversampled" );
    test_pipe.dither_buffer("buf:oversampled", volume::db2vol( -12 ) );
    test_pipe.process_with_inplace("proc:waveshaper", "buf:oversampled" );
    test_pipe.process_with_inplace("proc:down_filter","buf:oversampled" );
    test_pipe.decimate_into( "buf:oversampled", "buf:master" );

    test_pipe.write_buffer( "buf:master", "output/waveshaper.raw", binary_left );

    // write test report info to file 
    environment::write_samplerate_to_file( "output/test.samplerate" );
    environment::write_filename_to_file( "waveshaper.raw", "output/test.reportfile" );
    environment::write_fft_limits_to_file("output/test.report_fft_lims", (frequency_hz)100, (frequency_hz)20000);

    return NLDPROC_TEST_SUCCESS;
}

#endif
