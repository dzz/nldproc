#pragma once

#include "volume.h"

namespace nldproc {
    class volume {
        public:
            static double vol2db(double amplitude);
            static double db2vol(double db);
    };
}
