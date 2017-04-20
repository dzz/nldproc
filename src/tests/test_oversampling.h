int test_oversampling() {

    environment::configure_test_environment( (frequency_hz)20000, (sample_count)256 ); // 20khz SR / 48 samps

    os_factor       oversampling_amount = 32;    // 32x OS
    pipe            test_pipe;          
    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer(); 
 

    // configure a pipe, one IO buffer to 'master_buffer', at the default
    // samplerate, one oversampled buffer, os and ds filters
    
    test_pipe.assign_ptr_buffer( {"buf:master"}, master_buffer );
    test_pipe.create_oversampled_buffer( {"buf:master(os)" }, oversampling_amount );
    test_pipe.create_oversampler("oversampler:up", oversampling_amount, (frequency_hz)5000  );

    // fill IO buffer with a test signal
    sine::fill_range( 9500, test_pipe.get_mapped_buffer( "buf:master" ), 0, 63 ); //9.5k, close to nq, 16 samples
    sine::fill_range( 1000, test_pipe.get_mapped_buffer( "buf:master" ), 64, 127 ); 
    sine::fill_range( 440, test_pipe.get_mapped_buffer( "buf:master" ), 128, 255 ); 
    test::write_input_signal_test_data( &test_pipe, "buf:master");

    // upsample from buf:master -> buf:master(os)
    test_pipe.oversample_into("buf:master", "buf:master(os)", oversampling_amount, "oversampler:up" );
    
    // write test report info to file 
    test::write_mono_test_data( &test_pipe, "buf:master(os)", NLDPROC_FFT_LIMITS(100,10000) );

    return NLDPROC_TEST_SUCCESS;
}
