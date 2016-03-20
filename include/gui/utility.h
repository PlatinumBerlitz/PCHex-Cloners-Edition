#ifndef UTILITY_H
#define UTILITY_H

#include <string>

#include "Text.h"

std::string intTOstring(const int val, const int base);
int getTextWidth(raw_font* font, const int size, const std::string msg);

#endif /* UTILITY_H */

