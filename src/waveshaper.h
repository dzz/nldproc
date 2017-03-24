#pragma once
#include <vector>

namespace nldproc {

    typedef unsigned int spl_point_ID;

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
            double eval(double x);
            spl_point_ID    add_point( double x, double y, double k );
            void            del_point( const spl_point_ID id );
            spl_points      get_copyof_points();

        private:
            void sort_points();

            spl_point_ID id_seed;
            spl_points points;
    };
}

