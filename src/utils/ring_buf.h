#pragma once

namespace nldproc {

    typedef unsigned int ring_buf_size;
    typedef unsigned int ring_index;

    class ring_buf {
        public:
            ring_buf( ring_buf_size size );
            void insert( double* data, unsigned int count );
            void retrieve( double* target, unsigned int count );
            ~ring_buf();
        private:
            double* buffer;
            ring_index read;
            ring_index write;
            ring_buf_size length;
    };
}
