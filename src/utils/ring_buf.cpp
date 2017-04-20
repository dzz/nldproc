#include "ring_buf.h"
#include <cstring>

namespace nldproc {

    ring_buf::ring_buf( ring_buf_size size ) {

        buffers[0] = new double[size];
        buffers[1] = new double[size];

        for(int i =0; i<size;++i) {
            buffers[0][i] = 0.0;
            buffers[1][i] = 0.0;
        }
        this->length = size;

        write = 0;
        read = 0;

    }

    ring_buf::~ring_buf() {
        delete buffers[0];
        delete buffers[1];
    }

    void ring_buf::insert( double* data, unsigned int count ) {

        if( write + count > length ) {

            unsigned int delta;
            unsigned int remainder;

            delta = length - write;
            remainder = count-delta;


            std::memcpy(&buffers[0][write], data, sizeof( double ) * delta );
            std::memcpy(&buffers[0][0], &data[delta], sizeof( double ) * remainder );

            write = remainder;

        } else {
            std::memcpy(&buffers[0][write], data, sizeof( double ) * count );
            write += count;
        }
    }

    void ring_buf::retrieve( double* target, unsigned int count ) {

        if( read + count > length ) {
            unsigned int delta;
            unsigned int remainder;

            delta = length - read;
            remainder = count - delta;

            std::memcpy( &buffers[0][read], target, sizeof( double) * delta );
            std::memcpy( &target[delta], buffers[0], sizeof( double ) * remainder );

            read = remainder;
        } else {
            std::memcpy( target, &buffers[0][read],  sizeof( double ) * count );
            read+= count;
        }
    }

}
