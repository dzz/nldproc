#if ( NLDPROC_CURRENT_TEST == test_decimation )

int test_fir() {

    environment::configure_test_environment( (frequency_hz)20000, (sample_count)512 ); 

    pipe            test_pipe;          
    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer(); 

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
 
    test_pipe.map_processor( &test_fir, {"proc:fir"} );
    test_pipe.assign_ptr_buffer( {"buf:master"}, master_buffer );


    diracs::fill_range( (sample_spacing)10, 1, test_pipe.get_mapped_buffer( "buf:master" ), 0, 255 ); 
    sine::fill_range( 1500, test_pipe.get_mapped_buffer( "buf:master" ), 256, 511 ); 

    test_pipe.process_with_inplace("proc:fir","buf:master" );

    // write test report info to file 

    test::write_mono_test_data( &test_pipe, "buf:master", NLDPROC_FFT_LIMITS(100,10000) );

    return NLDPROC_TEST_SUCCESS;
}
#endif
