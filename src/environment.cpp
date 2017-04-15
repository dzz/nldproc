#include "environment.h"
#include <fstream>
#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>
#include "processor.h"

using namespace std::chrono;

namespace nldproc {

    const unsigned int CALIBRATION_SECS = 1;

    static std::vector<processor*> calibration_reqs;
    
    static high_resolution_clock::time_point implicit_time_start;
    static high_resolution_clock::time_point implicit_time_end;
    
    static double test_environment_length;
    
    static os_factor           active_oversampling = 1;
    static samplerate          active_base_samplerate = 44100;
    static buffer_chunksize    active_base_chunksize = 44100 * 2;

    void environment::enter_implicit_time() {
        
        implicit_time_start = std::chrono::high_resolution_clock::now();
    }

    void environment::register_calibration_req( deferred_processor instance ) {
        std::cout<<"REGISTERING :"<<instance<<"\n";
        calibration_reqs.push_back( (processor*)instance );
    }

    void environment::calibrate_processors() {
        std::cout<<" [ calibrating ... ]\n";

        std::for_each( calibration_reqs.begin(),
                       calibration_reqs.end(),
                       []( auto processor ) {
                            std::cout<<"  ->"<<processor<<"\n";
                            processor->calibrate();
                       });
    }
 
    void environment::exit_implicit_time() {
        implicit_time_end = std::chrono::high_resolution_clock::now();
    }

    
    void environment::calibrate() {
        buffer_chunksize tmp = active_base_chunksize;
        active_base_chunksize = active_base_samplerate * CALIBRATION_SECS;
        environment::calibrate_processors();
        active_base_chunksize = tmp;
    }

    void environment::configure_test_environment(int_frequency samplerate, buffer_chunksize length ) {

        active_base_samplerate = samplerate;
        active_base_chunksize = length;
        test_environment_length = (double)length/(double)samplerate;
    }

    samplerate environment::get_base_samplerate() {
        return active_base_samplerate;
    }

    samplerate environment::get_samplerate() {
        return environment::get_base_samplerate() * active_oversampling;
    }
    
    buffer_chunksize environment::get_base_buffer_chunksize() {
        return active_base_chunksize;
    }

    buffer_chunksize environment::get_buffer_chunksize() {
        return environment::get_base_buffer_chunksize() * active_oversampling;
    }

    void environment::write_filename_to_file( filename name, filename output_file ) {

        std::ofstream file( output_file );
        file << name;
        file.close();
    }

    void environment::write_samplerate_to_file( filename output_file ) {
        std::ofstream file( output_file );
        file << environment::get_samplerate();
        file.close();
    }

    void environment::write_to_file( filename output_file ) {
        std::ofstream file( output_file );
        file << environment::get_samplerate();
        file.close();
    }
    
    void environment::write_fft_limits_to_file( filename name, double min, double max ) {
        std::ofstream file( name  );
        file << min << "\n" << max << "\n";
        file.close();
    }

    void environment::write_implicit_time_to_file( filename name ) {

        duration<double> time_span = duration_cast<duration<double>>(implicit_time_end - implicit_time_start);
        std::cout << "It took me " << time_span.count() << " seconds." << std::endl;

        std::ofstream file( name  );
        file << time_span.count() <<" "<<test_environment_length;
        file.close();
    }


    void environment::set_oversampling(os_factor amount) {
        active_oversampling = amount;
    }

    os_factor environment::get_oversampling() {
        return active_oversampling;
    }
}
