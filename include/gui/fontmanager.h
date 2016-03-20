#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <map>
#include <string>
#include <sftd.h>

typedef sftd_font raw_font;

class FontManager {
    private:
        static std::map<std::string, raw_font*> fontmap;
        
        static void addNewFont(const std::string path);
        static raw_font* loadFromFile(const std::string path);
        
    public:
        static raw_font* getFont(const std::string path);
        static void freeAllFonts();
};

#endif /* FONTMANAGER_H */

