#include "environment.h"
#include <fstream>

namespace nldproc {

os_factor           active_oversampling = 1;
samplerate          active_base_samplerate = 44100;
buffer_chunksize    active_base_chunksize = 44100 * 2;

    void environment::configure_test_environment(int_frequency samplerate, buffer_chunksize length ) {
        active_base_samplerate = samplerate;
        active_base_chunksize = length;
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

    void environment::set_oversampling(os_factor amount) {
        active_oversampling = amount;
    }

    os_factor environment::get_oversampling() {
        return active_oversampling;
    }
}
