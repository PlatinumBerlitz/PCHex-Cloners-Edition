#ifndef POKEMON_H
#define POKEMON_H

#include "savefile.h"

class Pokemon {
    private:
        static const int PKMNLENGTH = Savefile::PKMNLENGTH;
        
        static const int NICKNAMEPOS = 0x40;
        static const int NICKNAMELENGTH = 26;
        static const int POKEDEXNUMBERPOS = 0x08;
        static const int POKEDEXNUMBERLENGTH = 2;
        static const int NATUREPOS = 0x1C;
        static const int NATURELENGTH = 1;
        static const int IVPOS = 0x74;
        static const int IVLENGTH = 4;
        static const int EXPPOINTPOS = 0x10;
        static const int EXPPOINTLENGTH = 4;
        static const int GENDERPOS = 0x1D;
        static const int GENDERLENGTH = 1;
        static const int ABILITYPOS = 0x14;
        static const int ABILITYLENGTH = 1;
        static const int ITEMPOS = 0x0A;
        static const int ITEMLENGTH = 2;
        static const int POKEBALLPOS = 0xDC;
        static const int POKEBALLLENGTH = 1;
        static const int OTIDPOS = 0x0C;
        static const int OTIDLENGTH = 2;
        static const int SOTIDPOS = 0x0E;
        static const int SOTIDLENGTH = 2;
        static const int PIDPOS = 0x18;
        static const int PIDLENGTH = 4;
        static const int MOVEPOS = 0x5A;
        static const int MOVELENGTH = 2;
        static const int EGGMOVEPOS = 0x6A;
        static const int EGGMOVELENGTH = 2;
        static const int EVPOS = 0x1E;
        static const int EVLENGTH = 1;
  
        char data[260];
        Savefile* save;
        int boxnumber;
        int indexnumber;
        
        void setPkmn();
        u32 expTableLookup(const int level, const int exptype);
        void rerollPID();
        
    public:
        static const int BOXMAX = Savefile::BOXMAX;
        static const int INDEXMAX = Savefile::INDEXMAX;
        static const int POKEMONNUMBER = Savefile::POKEMONNUMBER;
        static const int HP = 0;
        static const int ATK = 1;
        static const int DEF = 2;
        static const int SPE = 3;
        static const int SPA = 4;
        static const int SPD = 5;
        
        Pokemon() {}
        Pokemon(const int boxnumber, const int indexnumber, Savefile* save);
        
        int getBoxNumber() { return boxnumber; }
        int getIndexNumber() { return indexnumber; }
        std::wstring getNickname();
        u16 getPokedexNumber();
        u8 getNature();
        u8 getLevel();
        bool isEgg();
        bool isFemale();
        bool isShiny();
        bool isEVMAX();
        bool isGenderless();
        u8 getAbility();
        u16 getItem();
        u8 getBall();
        u16 getOTID();
        u16 getSOTID();
        u32 getPID();
        u16 getMove(const int nmove);
        u16 getEggmove(const int nmove);
        u8 getIV(const int stat);
        u8 getEV(const int stat);
        char* getDataPtr() { return data; }
        void setNickname(std::string nick);
        void setNature(const u8 nature);
        void setAbility(const u8 ability);
        void setItem(const u16 item);
        void setBall(const u8 ball);
        void setShiny(const bool shiny);
        void setMove(const u16 move, const int nmove);
        void setEggmove(const u16 move, const int nmove);
        void setIV(const u8 val, const int stat);
        void setEV(const u8 val, const int stat);
        void setLevel(const int lv);
        void setPokedexNumber(const u16 val);
        void setGender(const u8 val);
        void setDataPtr(char* data);
        bool clone(const int boxdestination, const int indexdestination, const bool commit);
        bool importPK6(std::string path);
        bool exportPK6(std::string path);
        bool savePkmn();
};

#endif /* POKEMON_H */

