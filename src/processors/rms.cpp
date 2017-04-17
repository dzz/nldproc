#include "rms.h"
#include "environment.h"
#include "utils/sinc.h"
#include <cmath>

namespace nldproc {

    rms::rms() {
        history = nullptr;
        window = nullptr;
    }
    
    latency_samples rms::get_latency() {
        return this->filter_size;
    }

    rms::rms(time_ms window_size) {
        rms::configure(window_size);
    }

    buffer_chunksize rms::get_filter_size() { 
        return this->filter_size;
    }

    void rms::configure(time_ms window_size) {

         std::cout<<"RMS WINDOW SIZE - "<<window_size<<"\n";

         buffer_chunksize size = (buffer_chunksize)((window_size/1000)*environment::get_samplerate());

         history = new sample[size];
         window = new sample[size];

         for(sample_index idx=0; idx<size; ++idx) {
             history[idx] = 0.0;
         }
         wHamming( window, size ); 
         this->filter_size = size;
         std::cout<<"RMS WINDOW FILTER SIZE - "<<this->filter_size<<"\n";
    }

    void rms::process_channel( channel_index channel, single_channel input, single_channel output ) {
        if(channel == 1)
            return;

        for(sample_index idx = 0; idx<environment::get_buffer_chunksize();++idx) {
            double squares = 0.0;

            for(sample_index t_idx=filter_size-1; t_idx>0;--t_idx) {
                history[t_idx] = history[t_idx-1];
            }
            history[0] = input[idx];
            output[idx] = 0.0;
            for(sample_index t_idx = 0; t_idx < filter_size; ++t_idx) {
                double windowed = history[t_idx] * this->window[t_idx];
                squares += windowed*windowed;
            }
            output[idx] = std::sqrt(squares / (double)filter_size);
        }
    }

    rms::~rms() {
        if(history!=nullptr) {
            delete history;
            delete window;
        }
    }

}

