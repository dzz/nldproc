#include "file.h"
#include <fstream>

namespace nldproc {
    namespace file {
        void unsafe_fill_from_file( filename raw_file, stereo_buffer target ) {

            #ifndef NLDPROC_PRODUCTION
            std::ifstream file(raw_file, std::ios::in | std::ios::binary | std::ios::ate );
            unsigned int size = file.tellg();
            file.seekg(0, std::ios::beg);
            char* memblck = new char[size];
            file.read(memblck, size );
            file.close();
            double* double_values = (double*)memblck;
            unsigned int r = 0;
            for(unsigned int i = 0; i<environment::get_buffer_chunksize(); ++i) {
                target[0][i] = double_values[r++];
                target[1][i] = double_values[r++]; 
            }
            delete [] memblck;
            #endif
        }
    }
}
