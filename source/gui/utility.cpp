#include <stdlib.h>
#include <sftd.h>

#include "utility.h"

std::string intTOstring(const int val, const int base) {
    char dummy[50];
    itoa(val, dummy, base);
    std::string toreturn(dummy);
    return toreturn;
}

int getTextWidth(raw_font* font, const int size, const std::string msg) {
    return sftd_get_text_width(font, size, msg.c_str());
}