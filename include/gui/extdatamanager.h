#ifndef EXTDATAMANAGER_H
#define EXTDATAMANAGER_H

#include <vector>
#include <string>

#include "savefile.h"

class ExtDataManager {
    private:
        static std::vector<std::string> guitext;
        static std::vector<u8> leveldata;
        static Savefile* saveptr;
        
    public:
        static const unsigned int ENGLISH = 1;
        
        static const int LVSTRING = 0;
        
        static std::string getBasePath();
        static int initialize(Savefile* save);
        static std::string getGuiText(const int msg) { return guitext[msg]; }
        static u8 getLevelType(const int val) { return leveldata[val]; }
        static Savefile* getSave() { return saveptr; }
};

#endif /* EXTDATAMANAGER_H */

