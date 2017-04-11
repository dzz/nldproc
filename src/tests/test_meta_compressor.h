int test_meta_compressor() {

    environment::configure_test_environment( (frequency_hz)44100, (sample_count)44100*10 ); 

    pipe            test_pipe;          
    stereo_buffer   master_buffer = test_pipe.create_unmapped_buffer(); 
    rms             test_rms(90);
    peakfollower    test_peakfollower(1.2);
    integrator      test_integrator(0.45);
    fast_tanh_gain  test_gain;


    file::unsafe_fill_from_file(  NLDPROC_TEST_RAW_AUDIO_FILE, master_buffer );
    test_pipe.assign_ptr_buffer( {"buf:master"}, master_buffer );
    test_pipe.create_buffer( { "buf:rms" } );
    test_pipe.create_buffer( { "buf:pf" } );
    test_pipe.create_buffer( { "buf:envelope" } );

    test_pipe.map_processor( &test_rms, {"proc:rms"} );
    test_pipe.map_processor( &test_peakfollower, {"proc:pf"} );
    test_pipe.map_processor( &test_integrator, {"proc:lpf"} );
    test_pipe.map_processor( &test_gain, {"proc:envgain"} );

    test_pipe.create_parameter( 
            "param:envelopeGain(dB)", (parameter_dispatches){ 
                {
                    [](double dB) { return volume::db2vol(dB); },
                    test_pipe.get_control( "proc:envgain", "control:gainVol" )
                } 
            }
    );
    test_pipe.set_parameter("param:envelopeGain(dB)", 18 );

    test::write_input_signal_test_data( &test_pipe, "buf:master");

    test_pipe.process_with( "proc:rms", "buf:master", "buf:rms" );
    test_pipe.process_with( "proc:pf", "buf:master", "buf:pf" );
    test_pipe.multiply_into( "buf:pf", "buf:rms", "buf:envelope");
    test_pipe.process_with_inplace("proc:lpf","buf:envelope");
    test_pipe.process_with_inplace("proc:envgain","buf:envelope");
    test_pipe.invert_from_max("buf:envelope", 2);
    test_pipe.multiply_into("buf:envelope","buf:master","buf:master");


    // write test report info to file 
    test::write_mono_test_data( &test_pipe, "buf:master", NLDPROC_FFT_LIMITS(10,20000) );

    return NLDPROC_TEST_SUCCESS;
}
