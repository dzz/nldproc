#pragma once

#include "environment.h"
#include "controls.h"
#include "processor.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

#include "DspFilters/Dsp.h"

namespace nldproc {

    #define DITHER_KERNEL_SIZE 2048

    #define RS_FILTER_ORDER 3

    const int resampling_filter_order = RS_FILTER_ORDER;

    typedef double frequency_hz;
    typedef unsigned int filetype;
    typedef unsigned int sample_count;

    const filetype binary_stereo = 0;
    const filetype binary_left = 2;
    const filetype binary_right = 3;

    typedef Dsp::SimpleFilter <Dsp::Bessel::LowPass<RS_FILTER_ORDER>, 2> oversampler;
    typedef Dsp::SimpleFilter <Dsp::Bessel::LowPass<RS_FILTER_ORDER>, 2> downsampler;

    typedef std::unordered_map< alias, oversampler* > oversampler_map;
    typedef std::unordered_map< alias, downsampler* > downsampler_map;

    typedef std::vector<alias> alias_list;
    typedef std::unordered_map< alias, processor* > processor_map;
    typedef std::unordered_map< alias, stereo_buffer > buffer_map;
    typedef std::vector< stereo_buffer > buffer_collection;
    typedef std::string filename;
    
    struct parameter_dispatch {
        std::function<double(double)> transform;
        control* target;
    };

    typedef std::vector< parameter_dispatch > parameter;
    typedef std::vector< parameter_dispatch > parameter_dispatches;
    typedef std::unordered_map< alias, parameter > parameter_map;

    typedef double amplitude;

    class pipe {
        public:
            pipe();
            ~pipe();
            
            processor* get_processor( alias name );
            control* get_control( alias processor, control_name control);

            double find_max( alias buffer_name );
            void create_parameter( alias name, parameter parameter );
            void set_parameter( alias parameter, double value );
            void map_processor( processor* processor, alias name );
            void map_managed_processor( processor* processor, alias name );
            void create_buffer( alias_list aliases );
            void create_oversampled_buffer( alias_list aliases, os_factor amount );
            void assign_ptr_buffer( alias_list aliases, stereo_buffer buffer );
            void process_with( alias processor, alias buffer_from, alias buffer_to );
            void process_with_inplace( alias processor, alias buffer );
            void process( stereo_buffer buffer );
            void dither_buffer( alias buffer, amplitude threshold );
            stereo_buffer create_unmapped_buffer();
            stereo_buffer create_unmapped_buffer(buffer_chunksize size);
            stereo_buffer get_mapped_buffer( alias alias );
            void dump_buffer( alias buffer_alias );
            void write_buffer( alias buffer_alias, filename output_file, filetype output_type );
            void oversample_into( alias from, alias to, os_factor amount, alias oversampler );
            void downsample_into( alias buffer_from, alias buffer_to, alias downsampler );
            void decimate_into( alias buffer_from, alias buffer_to );

            void difference_into( alias left, alias right, alias buffer );
            void add_into( alias left, alias right, alias buffer );
            void multiply_into( alias left, alias right, alias buffer );
            void multiply_into_scalar( alias left, double scalar, alias buffer );
            void invert_from_max( alias buffer, double max);
            void copy_into( alias left, alias right );
            void create_oversampler( alias name, os_factor amount, frequency_hz half_band );
            void create_downsampler( alias name, os_factor amount, frequency_hz half_band  );
            void upmix( alias name );
            void xfade_into_using( alias a, alias b, alias target, alias control );
        private:
            stereo_buffer dither_kernel;
            sample_index dither_idx;
            processor_map processors;
            buffer_map buffers;
            buffer_collection unique_buffers;
            buffer_chunksize chunk_size;
            parameter_map parameters;
            oversampler_map oversamplers;
            downsampler_map downsamplers;
            alias_list managed_processors;
            static void delete_unmapped_buffer( stereo_buffer buffer );
    }; 

    class buffer_utils {
        public: 
            static double find_max_abs( stereo_buffer buffer ) {
                double max = 0.0;
                for(sample_index i=0; i<environment::get_buffer_chunksize();++i) {
                    double l = fabs( buffer[0][i]);
                    double r = fabs( buffer[1][i]);
        
                    if(l>max) max = l;
                    if(r>max) max = r;
                }
                return (unsigned int)(max*1000);
        }
    };
}
