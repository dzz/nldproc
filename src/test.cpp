#include "test_signals/whitenoise.h"
#include "test_signals/sine.h"
#include "test_signals/diracs.h"

#include "utils/volume.h"
#include "utils/file.h"

#include "pipe.h"
#include "environment.h"

#include "processors/processors.h"

#include "tests.h"

namespace nldproc {
    namespace test {

        void write_input_signal_test_data( pipe* pipe, alias buffer ) {
            std::string filename = "input." + std::string(NLDPROC_TOSTRING( NLDPROC_CURRENT_TEST )) + ".raw";
            std::cout<<"Writing File: "<<filename<<"\n";
            pipe->write_buffer( buffer, "output/" + filename , binary_left );
        }

        void write_mono_test_data( pipe* pipe, alias buffer, frequency_hz fft_low, frequency_hz fft_hi ) {

            environment::exit_implicit_time();

            std::string filename = std::string(NLDPROC_TOSTRING( NLDPROC_CURRENT_TEST )) + ".raw";

            std::cout<<"Writing File: "<<filename<<"\n";
            pipe->write_buffer( buffer, "output/" + filename , binary_left );
            environment::write_samplerate_to_file( "output/test.samplerate" );
            environment::write_filename_to_file( filename, "output/test.reportfile" );
            environment::write_fft_limits_to_file("output/test.report_fft_lims", (frequency_hz)fft_low, (frequency_hz)fft_hi);
            environment::write_implicit_time_to_file("output/implicit_time");
        }
    }
    #include "test_includes.h"
}
