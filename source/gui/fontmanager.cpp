#include <string>

#include "fontmanager.h"

std::map<std::string, raw_font*> FontManager::fontmap;

raw_font* FontManager::getFont(const std::string path) {
    std::map<std::string, raw_font*>::iterator it = fontmap.find(path);
    
    if( it == fontmap.end() )
        addNewFont(path);
    
    return fontmap.at(path);
    
}

void FontManager::addNewFont(const std::string path) {
    raw_font* newfont = loadFromFile(path);
    std::pair<std::string, raw_font*> toadd(path, newfont);
    fontmap.insert(toadd);
}

raw_font* FontManager::loadFromFile(const std::string path) {
    return sftd_load_font_file(path.c_str());
}

void FontManager::freeAllFonts() {
    for(std::map<std::string, raw_font*>::iterator it = fontmap.begin(); it != fontmap.end(); it++)
        sftd_free_font(it->second);
}
