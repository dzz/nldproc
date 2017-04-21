#include "ring_buf.h"
#include <cstring>

namespace nldproc {

    ring_buf::ring_buf( ring_buf_size size ) {

        buffer = new double[size];

        for(int i =0; i<size;++i) {
            buffer[i] = 0.0;
        }
        this->length = size;

        write = 0;
        read = 0;

    }

    ring_buf::~ring_buf() {
        delete buffer;
    }

    void ring_buf::insert( double* data, unsigned int count ) {

        if( write + count > length ) {

            unsigned int delta;
            unsigned int remainder;

            delta = length - write;
            remainder = count-delta;


            std::memcpy(&buffer[write], data, sizeof( double ) * delta );
            std::memcpy(&buffer[0], &data[delta], sizeof( double ) * remainder );

        } else {
            std::memcpy(&buffer[write], data, sizeof( double ) * count );
        }
    }

    void ring_buf::retrieve( double* target, unsigned int count ) {
        if( read + count > length ) {
            unsigned int delta;
            unsigned int remainder;

            delta = length - read;
            remainder = count - delta;

            std::memcpy( &buffer[read], target, sizeof( double) * delta );
            std::memcpy( &target[delta], buffer, sizeof( double ) * remainder );
        } else {
            std::memcpy( target, &buffer[read],  sizeof( double ) * count );
        }
    }

    void ring_buf::advance_read( unsigned int count ) {
        if( read + count > length ) {
            unsigned int delta;
            unsigned int remainder;

            delta = length - read;
            remainder = count - delta;
            
            read = remainder;
        } else {
            read += count;
        }
    }

    void ring_buf::advance_write( unsigned int count ) {
        if( write + count > length ) {
            unsigned int delta;
            unsigned int remainder;

            delta = length - write;
            remainder = count - delta;
            
            write = remainder;
        } else {
            write += count;
        }
    }

}
