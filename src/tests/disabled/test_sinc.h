int test_sinc() {

    environment::configure_test_environment( (frequency_hz)44100, (sample_count)44100 ); 

    pipe            test_pipe;          
    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer(); 

    sinc_filter     test_sinc( 32, 0.25, SINC_LOWPASS );
 
    test_pipe.map_processor( &test_sinc, {"proc:fir"} );
    test_pipe.assign_ptr_buffer( {"buf:master"}, master_buffer );


    sine::fill_buffer_sweep(40,20000, master_buffer);
    test::write_input_signal_test_data( &test_pipe, "buf:master");

    test_pipe.process_with_inplace("proc:fir","buf:master" );

    test::time_shift_forward( &test_pipe, 32, "buf:master");
    test::write_mono_test_data( &test_pipe, "buf:master", NLDPROC_FFT_LIMITS(100,10000) );

    return NLDPROC_TEST_SUCCESS;
}
