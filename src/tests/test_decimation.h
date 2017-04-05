#if ( NLDPROC_CURRENT_TEST == test_decimation )


int test_decimation() {

    environment::configure_test_environment( (frequency_hz)20000, (sample_count)256 ); 

    os_factor       oversampling_amount = 4;    
    pipe            test_pipe;          
    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer(); 
 
    test_pipe.assign_ptr_buffer( {"buf:master"}, master_buffer );
    test_pipe.create_oversampled_buffer( {"buf:master(os)" }, oversampling_amount );
    test_pipe.create_oversampler("oversampler:up", oversampling_amount, (frequency_hz)5000  );

    sine::fill_range( 9500, test_pipe.get_mapped_buffer( "buf:master" ), 0, 63 ); //9.5k, close to nq, 16 samples
    sine::fill_range( 1000, test_pipe.get_mapped_buffer( "buf:master" ), 64, 127 ); 
    sine::fill_range( 440, test_pipe.get_mapped_buffer( "buf:master" ), 128, 255 ); 

    test_pipe.oversample_into("buf:master", "buf:master(os)", oversampling_amount, "oversampler:up" );
    test_pipe.decimate_into("buf:master(os)", "buf:master" ); 
    test_pipe.write_buffer( "buf:master", "output/decimation.raw", binary_left );

    environment::write_samplerate_to_file( "output/test.samplerate" );
    environment::write_filename_to_file( "decimation.raw", "output/test.reportfile" );
    environment::write_fft_limits_to_file("output/test.report_fft_lims", (frequency_hz)100, (frequency_hz)10000);

    return NLDPROC_TEST_SUCCESS;
}
#endif
