#pragma once

namespace nldproc {

    class volume {
        public:
            inline static double vol2db(double amplitude);
            inline static double db2vol(double db);
    };
}
