#pragma once
#include <vector>

namespace nldproc {

    typedef unsigned int spl_point_ID;
    typedef unsigned int spl_idx;

    struct spl_point{
        double x;
        double y;
        double k;
        spl_point_ID id;
    };

    typedef std::vector<spl_point> spl_points;

    class waveshaper {

        public:
            waveshaper();
            ~waveshaper();
            void process(unsigned int samples, double* channels);
            spl_point_ID    add_point( double x, double y, double k );
            void            del_point( const spl_point_ID id );
            spl_points      get_copyof_points();
            void            commit();

        private:
            void sort_points();

            double* _xs;
            double* _ys;
            double* _ks;

            inline double xs( spl_idx idx );
            inline double ys( spl_idx idx );
            inline double ks( spl_idx idx );

            spl_point_ID id_seed;
            spl_points points;
    };
}

