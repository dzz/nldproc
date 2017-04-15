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

        void time_shift_forward( pipe* pipe, sample_count amount, alias buffer_name ) {
            unsigned int read_ptr = amount;
            stereo_buffer buffer = pipe->get_mapped_buffer( buffer_name );
            for(sample_index idx =0; read_ptr < environment::get_buffer_chunksize();++idx) {
                buffer[0][idx] = buffer[0][read_ptr];
                buffer[1][idx] = buffer[1][read_ptr];
                read_ptr++;
            }
        }

        void write_input_signal_test_data( pipe* pipe, alias buffer ) {
            std::string filename = "input." + std::string(NLDPROC_TOSTRING( NLDPROC_CURRENT_TEST )) + ".raw";
            std::cout<<"Writing File: "<<filename<<"\n";
            pipe->write_buffer( buffer, "output/" + filename , binary_left );

            environment::calibrate();
            environment::enter_implicit_time();
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

        void write_additional_buffer( pipe* pipe, alias buffer ) {
            pipe->write_buffer( buffer, "output/extra_" + buffer , binary_left );
        }
    }

    #include "test_includes.h"
}
