namespace nldproc {

    typedef double**     stereo_buffer;
    class processor {
        public:
            virtual void process(stereo_buffer input, stereo_buffer output);
    }
}
