#pragma once

namespace nldproc {

#include "test.h"

#ifndef NLDPROC_CURRENT_TEST
    #define NLDPROC_CURRENT_TEST test_derivative
#endif

int NLDPROC_CURRENT_TEST ();

#define NLDPROC_TEST_RAW_AUDIO_FILE "/home/devon/drum_test.raw"
#define NLDPROC_STRINGIFY(x) #x
#define NLDPROC_TOSTRING(x) NLDPROC_STRINGIFY(x)

#define NLDPROC_TEST_SUCCESS 0
#define NLDPROC_TEST_FAILURE 1


#define NLDPROC_FFT_LIMITS(X, Y)  X,Y
    namespace test {
        void write_mono_test_data( pipe* pipe, alias buffer, frequency_hz fft_low, frequency_hz fft_hi );
        void write_input_signal_test_data( pipe* pipe, alias buffer );
    }
}



