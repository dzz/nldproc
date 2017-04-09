namespace nldproc {

#ifndef NLDPROC_CURRENT_TEST
    #define NLDPROC_CURRENT_TEST test_waveshaper
#endif

#define NLDPROC_STRINGIFY(x) #x
#define NLDPROC_TOSTRING(x) NLDPROC_STRINGIFY(x)

#define NLDPROC_TEST_SUCCESS 0
#define NLDPROC_TEST_FAILURE 1

#include "tests/test_oversampling.h"
#include "tests/test_decimation.h"
#include "tests/test_fir.h"
#include "tests/test_sinc.h"
#include "tests/test_dither.h"
#include "tests/test_waveshaper.h"

}



