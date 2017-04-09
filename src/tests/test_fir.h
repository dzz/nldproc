#if ( NLDPROC_CURRENT_TEST == test_decimation )

int test_fir() {

    environment::configure_test_environment( (frequency_hz)20000, (sample_count)256 ); 

    pipe            test_pipe;          

    double fir_kernel[] = {
        -0.2,
        0.5,
        -1.0,
        1.0,
        -1.0,
        0.5,
        -0.2
    };

    fir             test_fir( 7, fir_kernel );
    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer(); 
 
    test_pipe.map_processor( &test_fir, {"proc:fir"} );

    test_pipe.assign_ptr_buffer( {"buf:master"}, master_buffer );
    diracs::fill_range( (sample_spacing)10, 1, test_pipe.get_mapped_buffer( "buf:master" ), 0, 256 ); 


    test_pipe.process_with_inplace("proc:fir","buf:master" );

    test_pipe.write_buffer( "buf:master", "output/fir.raw", binary_left );

    // write test report info to file 
    environment::write_samplerate_to_file( "output/test.samplerate" );
    environment::write_filename_to_file( "fir.raw", "output/test.reportfile" );
    environment::write_fft_limits_to_file("output/test.report_fft_lims", (frequency_hz)100, (frequency_hz)10000);

    return NLDPROC_TEST_SUCCESS;
}
#endif
