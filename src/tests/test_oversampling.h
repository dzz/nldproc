#if ( NLDPROC_CURRENT_TEST == test_oversampling )

int test_oversampling() {

    environment::configure_test_environment( 20000, 32 ); // 20khz SR / 32 samps

    os_factor       oversampling_amount = 2;    // 2x OS
    pipe            test_pipe;          
    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer(); 
 

    // configure a pipe, one IO buffer to 'master_buffer', at the default
    // samplerate, one oversampled buffer, os and ds filters
    
    test_pipe.assign_ptr_buffer( {"buf:master"}, master_buffer );
    test_pipe.create_oversampled_buffer( {"buf:master(os)" }, oversampling_amount );
    test_pipe.create_oversampler("oversampler:up", oversampling_amount  );
    test_pipe.create_downsampler("downsampler:down", oversampling_amount);

    // fill IO buffer with a test signal
    sine::fill_buffer( 9500, test_pipe.get_mapped_buffer( "buf:master" ) ); //9.5k, close to nq

    // upsample from buf:master -> buf:master(os)
    test_pipe.oversample_into("buf:master", "buf:master(os)", oversampling_amount, "oversampler:up" );

    // write the buffer to file
    test_pipe.write_buffer( "buf:master(os)", "output/oversampling.raw", binary_left );

    // write test report info to file 
    environment::write_samplerate_to_file( "output/test.samplerate" );
    environment::write_filename_to_file( "oversampling.raw", "output/test.reportfile" );

    return NLDPROC_TEST_SUCCESS;
}
#endif
