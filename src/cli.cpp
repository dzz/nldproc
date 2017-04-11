#include <iostream>
#include <random>
#include <algorithm>

#include "test_signals/whitenoise.h"
#include "test_signals/sine.h"
#include "test_signals/diracs.h"

#include "utils/volume.h"
#include "utils/file.h"

#include "pipe.h"
#include "environment.h"

#include "processors/processors.h"

#include "build.h"
#include "tests.h"

using namespace nldproc;

void print_banner() {
    std::cout<<"nldproc (build "<<NLDPROC_BUILDNUM << ")\n\n";
    std::cout<<"running test: "<< NLDPROC_TOSTRING(NLDPROC_CURRENT_TEST)<< "\n" << "-=-=-=-=-=-=-=-=-=-=-=" << "\n";
}

int main() {
    print_banner();
    return NLDPROC_CURRENT_TEST();
}
