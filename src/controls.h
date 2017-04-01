#pragma once

#include <string>

namespace nldproc {
    struct control {
        double state;
        double impulse; 
        double filter_coef;
        double inv_filter_coef;
    };

    typedef std::string  control_name;
    typedef double       control_value;

}




