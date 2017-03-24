#include <iostream>
#include <vector>
#include <algorithm>
#include "waveshaper.h"

namespace nldproc {

    waveshaper::waveshaper() {
        this->id_seed = 0;
        this->add_point( -1.0, -1.0, 1.0 );
        this->add_point( 1.0, 1.0, -1.0 );
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

            std::cout<<point.id<<"\n";
            std::cout<<id<<"\n";

            if(point.id != id)  {
                ptr->push_back(point);
            }
        });
        this->points = new_points;
    }

    double waveshaper::eval(double x) {

        return 0.0;    
    }

}
