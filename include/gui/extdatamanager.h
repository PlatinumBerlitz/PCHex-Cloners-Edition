#ifndef EXTDATAMANAGER_H
#define EXTDATAMANAGER_H

#include <vector>
#include <string>

#include "savefile.h"

class ExtDataManager {
    private:
        static std::vector<std::string> guitext;
        static std::vector<std::string> species;
        static std::vector<std::string> natures;
        static std::vector<std::string> abilities;
        static std::vector<std::string> items;
        static std::vector<std::string> balls;
        static std::vector<std::string> moves;
        static std::vector<u8> leveldata;
        static std::vector<u8> hpdata;
        static std::vector<u8> atkdata;
        static std::vector<u8> defdata;
        static std::vector<u8> spedata;
        static std::vector<u8> spadata;
        static std::vector<u8> spddata;
        static std::vector<u8> formdata;
        static Savefile* saveptr;
        
    public:
        static const unsigned int ENGLISH = 1;
        static const unsigned int FRENCH = 2;
        static const unsigned int ITALIAN = 4;
        static const unsigned int SPANISH = 5;
        static const unsigned int NEDERLAND = 8;
        
        static const int LVSTRING = 0;
        static const int BOXSTRING = 1;
        static const int EDITSTRING = 2;
        static const int IMPORTSTRING = 3;
        static const int CLONESTRING = 4;
        static const int CANCELSTRING = 5;
        static const int CHOOSESTRING = 6;
        static const int SELECTCLONINGSTRING = 7;
        static const int SUCCESSSSTRING = 8;
        static const int FAILEDSTRING = 9;
        static const int MULTIPLESELECTSTRING = 10;
        static const int SELECTPK6STRING = 11;
        static const int NOCONTENTSTRING = 12;
        static const int PREVSTRING = 13;
        static const int NEXTSTRING = 14;
        static const int SEARCHSTRING = 15;
        static const int SPECIESSTRING = 16;
        static const int NATURESTRING = 17;
        static const int SELECTNATURESTRING = 18;
        static const int SAVESTRING = 19;
        static const int EXPORTSTRING = 20;
        static const int ABILITYSTRING = 21;
        static const int SELECTABILITYSTRING = 22;
        static const int ITEMSTRING = 23;
        static const int SELECTITEMSTRING = 24;
        static const int BALLSTRING = 25;
        static const int SELECTBALLSTRING = 26;
        static const int SHINYSTRING = 27;
        static const int YESSTRING = 28;
        static const int NOSTRING = 29;
        static const int OTSTRING = 30;
        static const int SELECTSPECIESSTRING = 31;
        static const int COMBATTABSTRING = 32;
        static const int GENERALTABSTRING = 33;
        static const int MOVESSTRING = 34;
        static const int EGGMOVESSTRING = 35;
        static const int SELECTMOVESTRING = 36;
        static const int SELECTEGGMOVESTRING = 37;
        static const int STATSSTRING = 38;
        static const int HPSTRING = 39;
        static const int ATKSTRING = 40;
        static const int DEFSTRING = 41;
        static const int SPASTRING = 42;
        static const int SPDSTRING = 43;
        static const int SPESTRING = 44;
        static const int IVSTRING = 45;
        static const int EVSTRING = 46;
        static const int TOTALSTRING = 47;
        static const int LOADINGSTRING = 48;
        
        static std::string getBasePath();
        static int initialize(Savefile* save);
        static std::string getGuiText(const int msg) { return guitext[msg]; }
        static u8 getLevelType(const int val) { return leveldata[val]; }
        static u8 getBaseHP(const int val) { return hpdata[val]; }
        static u8 getBaseATK(const int val) { return atkdata[val]; }
        static u8 getBaseDEF(const int val) { return defdata[val]; }
        static u8 getBaseSPE(const int val) { return spedata[val]; }
        static u8 getBaseSPA(const int val) { return spadata[val]; }
        static u8 getBaseSPD(const int val) { return spddata[val]; }
        static u8 getFormData(const int val) { return formdata[val]; }
        static std::string getSpeciesName(const int val) { return species[val]; }
        static std::vector<std::string> getSpeciesNameVector() { return species; }
        static std::string getNatureName(const int val) { return natures[val]; }
        static std::vector<std::string> getNaturesNameVector() { return natures; }
        static std::string getAbilityName(const int val) { return abilities[val]; }
        static std::vector<std::string> getAbilitiesNameVector() { return abilities; }
        static std::string getItemName(const int val) { return items[val]; }
        static std::vector<std::string> getItemsNameVector() { return items; }
        static std::string getBallName(const int val) { return balls[val]; }
        static std::vector<std::string> getBallsNameVector() { return balls; }
        static std::string getMoveName(const int val) { return moves[val]; }
        static std::vector<std::string> getMovesNameVector() { return moves; }
        static Savefile* getSave() { return saveptr; }
};

#endif /* EXTDATAMANAGER_H */

