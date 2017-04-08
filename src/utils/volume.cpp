#include "volume.h"
#include <cmath>


namespace nldproc {

    double volume::vol2db(double amplitude) {
        return 20 * log10(amplitude);
    }

    double volume::db2vol(double db) {
        return pow(10, db/20);
    }
}
