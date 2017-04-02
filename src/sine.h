#pragma once

#include "test_signal.h"
#include "environment.h"
#include "processor.h"
#include "pipe.h"

namespace nldproc {
    class sine : public test_signal {
        public:
            static void generate_sweep(double start_hz, double end_hz, buffer_chunksize samples, single_channel channel);
            static void fill_buffer_sweep( double start_hz, double end_hz, stereo_buffer channels );
            static void generate(double hz, buffer_chunksize samples, single_channel channel );
            static void fill_buffer(double hz, stereo_buffer buffer);
    };
}


