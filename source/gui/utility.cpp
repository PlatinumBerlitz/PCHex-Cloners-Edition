#include <stdlib.h>

#include "utility.h"

std::string intTOstring(const int val, const int base) {
    char dummy[50];
    itoa(val, dummy, base);
    std::string toreturn(dummy);
    return toreturn;
}