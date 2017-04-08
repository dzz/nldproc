#include "sine.h"
#include "environment.h"
#include "processor.h"

#include <cmath>

namespace nldproc {

constexpr double pi() { return std::atan(1)*4; }

    void sine::generate(double hz, buffer_chunksize samples, single_channel channel) {
        for(sample_index i=0; i<samples;++i) {
            double t = (double)i / (double)environment::get_samplerate();
            channel[i] = sin( t*hz*2*pi() );
        }
    }

    void sine::fill_range( double hz, stereo_buffer channels, sample_index start, sample_index end) {
        for(sample_index i=start; i<end;++i) {
            double t = (double)i / (double)environment::get_samplerate();
            channels[0][i] = sin( t*hz*2*pi() );
            channels[1][i] = sin( t*hz*2*pi() );
        }
    }

    void sine::fill_buffer( double hz, stereo_buffer channels ) {
        sine::generate_sweep( hz, hz, environment::get_buffer_chunksize(), channels[0] );
        sine::generate_sweep( hz, hz, environment::get_buffer_chunksize(), channels[1] );
    }

    void sine::fill_buffer_sweep( double start_hz, double end_hz, stereo_buffer channels ) {
        sine::generate_sweep( start_hz, end_hz, environment::get_buffer_chunksize(), channels[0] );
        sine::generate_sweep( start_hz, end_hz, environment::get_buffer_chunksize(), channels[1] );
    }

    void sine::generate_sweep(double start_hz, double end_hz, buffer_chunksize samples, single_channel channel) {

        double t = 0;
        for(sample_index i=0; i<samples;++i) {

            double idx = (double)i/(double)samples; 
            double hz = start_hz*(1-idx) + (end_hz*idx);

            t += (1.0/environment::get_samplerate()) * hz;
            channel[i] = sin( t*2*pi() );
        }
    }
}
