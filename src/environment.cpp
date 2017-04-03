#include "environment.h"
#include <fstream>

namespace nldproc {

os_factor oversampling = 1;

    samplerate environment::get_base_samplerate() {
        return 96000;
    }

    samplerate environment::get_samplerate() {
        return environment::get_base_samplerate() * oversampling;
    }
    
    buffer_chunksize environment::get_base_buffer_chunksize() {
        return 4096;
    }

    buffer_chunksize environment::get_buffer_chunksize() {
        return environment::get_base_buffer_chunksize() * oversampling;
    }

    void environment::write_to_file( filename output_file ) {
        std::ofstream file( output_file );
        file << environment::get_samplerate();
        file.close();
    }

    void environment::set_oversampling(os_factor amount) {
        oversampling = amount;
    }

    os_factor environment::get_oversampling() {
        return oversampling;
    }
}
