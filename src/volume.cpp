#include "volume.h"
#include <cmath>

namespace nldproc {

    inline double volume::vol2db(double amplitude) {
        return 20 * log10(amplitude);
    }

    inline double volume::db2vol(double db) {
        return pow(10, db/20);
    }
}
