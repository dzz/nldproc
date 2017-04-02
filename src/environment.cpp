#include "environment.h"
#include <fstream>

namespace nldproc {

    samplerate environment::get_samplerate() {
        return 44100;
    }
    
    buffer_chunksize environment::get_buffer_chunksize() {
        return 11025;
    }

    void environment::write_to_file( filename output_file ) {
        std::ofstream file( output_file );
        file << environment::get_samplerate();
        file.close();
    }
}
