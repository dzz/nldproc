#include <iostream>
#include <vector>
#include <algorithm>
#include "waveshaper.h"
#include "processor.h"
#include "environment.h"
#include "DspFilters/Dsp.h"

namespace nldproc {

    waveshaper::waveshaper() {
        this->id_seed = 0;
        this->add_point( -1.0, -1.0, 1.0 );
        this->add_point( -0.5, 0.3, 1.0 );
        this->add_point( 0.0, 0.0, 0.0 );
        this->add_point( 1.0, 1.0, -1.0 );
        this->_xs = nullptr;
        this->_ys = nullptr;
        this->_ks = nullptr;
        this->commit();
    }

    waveshaper::~waveshaper() {
        if(_xs!=nullptr) delete _xs;
        if(_ys!=nullptr) delete _ys;
        if(_ks!=nullptr) delete _ks;
    }


    spl_point_ID waveshaper::add_point( double x, double y, double k ) {
        spl_point next = { x,y,k, this->id_seed };

        this->points.push_back( next );
        this->sort_points();

        return this->id_seed++;
    }

    void waveshaper::sort_points() {
        std::sort(  this->points.begin(),
                    this->points.end(),
                    []( spl_point &a, spl_point &b) {
                        return a.x < b.x;
                    });
    }

    spl_points waveshaper::get_copyof_points() {
        return spl_points( this->points );
    }

    void waveshaper::del_point( const spl_point_ID id) {
        spl_points new_points;
        auto ptr = &new_points;

        std::for_each( 
            this->points.begin(), 
            this->points.end(), 
            [ ptr, id ](auto point) { 
            if(point.id != id)  {
                ptr->push_back(point);
            }
        });
        this->points = new_points;
        this->sort_points();
    }

    inline double waveshaper::xs( spl_idx idx ) {
        return _xs[idx];
    }

    inline double waveshaper::ys( spl_idx idx ) {
        return _ys[idx];
    }

    inline double waveshaper::ks( spl_idx idx ) {
        return _ks[idx];
    }


    void waveshaper::process(stereo_buffer input, stereo_buffer output ) {
        processor::process( input, output );
    }

    void waveshaper::process_channel(channel_index index, single_channel input, single_channel output ) {

            sample_index        position        = 0;
            sample_index        total_samples   = environment::get_buffer_chunksize();
            sample_addr         cur_sample      = nullptr;
            spl_idx             i;
            double              t,a,b,q;

            while(position < total_samples) {
                cur_sample  = &input[position];
                i           = 1;

                while( xs(i) < *cur_sample) i++;

                t = (*cur_sample - xs(i-1)) / (xs(i) - xs(i-1));
                a =  ks(i-1)*(xs(i)-xs(i-1)) - (ys(i)-ys(i-1));
                b = -ks(i  )*(xs(i)-xs(i-1)) + (ys(i)-ys(i-1));
                q = (1-t)*ys(i-1) + t*ys(i) + t*(1-t)*(a*(1-t)+b*t);

                output[position++] = q;
            }
    }

    void waveshaper::commit() {

        if( _xs == nullptr) delete _xs;
        if( _ys == nullptr) delete _ys;
        if( _ks == nullptr) delete _ks;

        _xs = new double[ points.size() ];
        _ys = new double[ points.size() ];
        _ks = new double[ points.size() ];

        for(spl_idx i=0; i< points.size();++i ) {
            _xs[i] = points[i].x;
            _ys[i] = points[i].y;
            _ks[i] = points[i].k;
        }
    }
}
