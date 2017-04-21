#include "fir.h"
#include <iostream>

namespace nldproc {

    fir::fir() {

    }

    fir::fir( tapcount size, coefficients spec) {
        this->configure( size, spec );
    }

    void fir::configure( tapcount size, coefficients spec ) {

        history[0] = new ring_buf(environment::get_buffer_chunksize() + size );
        history[1] = new ring_buf(environment::get_buffer_chunksize() + size );
        tmp = new double[ environment::get_buffer_chunksize() + size ];

        history[0]->advance_write(size);
        history[1]->advance_write(size);

        filter = new coefficient[size];
        for(sample_index i=0; i< size; ++i) {
            filter[i] = spec[size-(i+1)];
        }
        filter_size = size;
    }


    void fir::process_channel( channel_index channel, single_channel input, single_channel output ) {

        history[channel]->insert( input, environment::get_buffer_chunksize() );
        history[channel]->advance_write( environment::get_buffer_chunksize() );
        history[channel]->retrieve( tmp, environment::get_buffer_chunksize() + filter_size );
        history[channel]->advance_read( environment::get_buffer_chunksize() );

        for(sample_index idx = 0; idx<environment::get_buffer_chunksize();++idx) {
            output[idx] = 0.0;
            for(tapcount t_idx = 0; t_idx < filter_size; ++t_idx) {
                output[idx]+= tmp[ t_idx + idx ] * this->filter[t_idx];
            }
        }
    }

    fir::~fir() {
        delete  history[0];
        delete  history[1];
        delete [] filter;
    }

}
