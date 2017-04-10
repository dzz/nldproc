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

    test::write_mono_test_data( &test_pipe, "buf:master", NLDPROC_FFT_LIMITS(100,10000) );

    return NLDPROC_TEST_SUCCESS;
}
