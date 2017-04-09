#if ( NLDPROC_CURRENT_TEST == test_dither )

int test_dither() {

    environment::configure_test_environment( (frequency_hz)44100, (sample_count)44100 ); 

    pipe            test_pipe;          
    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer(); 

    sinc_filter     test_sinc( 512, 0.25, SINC_LOWPASS );
 
    test_pipe.map_processor( &test_sinc, {"proc:fir"} );
    test_pipe.assign_ptr_buffer( {"buf:master"}, master_buffer );

    sine::fill_buffer_sweep(15000,40, master_buffer);

    test_pipe.process_with_inplace("proc:fir","buf:master" );
    test_pipe.dither_buffer("buf:master", volume::db2vol( -96 ) );

    test_pipe.write_buffer( "buf:master", "output/dither.raw", binary_left );

    // write test report info to file 
    test::write_mono_test_data( &test_pipe, "buf:master", NLDPROC_FFT_LIMITS(100,20000) );

    return NLDPROC_TEST_SUCCESS;
}

#endif
