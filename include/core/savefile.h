#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <3ds.h>
#include <string>

class Savefile {
    private:
        char* save;
        
        static const int OFFSET = 0x5400;
        
        u32 getCHKOffset(const int index);
        u32 getCHKLenght(const int index);
        u16 ccitt16(char* data, const int size);
        void calculateChecksum();
        u32 seedStep(const u32 seed);
        void shuffleArray(char* pkmn, const u32 encryptionkey);
        void decryptPkmn(char* pkmn);
        int getPkmnAddress(const int boxnumber, const int indexnumber);
        void calculatePKMNChecksum(char* data);
        void encryptPkmn(char* pkmn);
        
    public:
        static const int PKMNLENGTH = 232;
        static const int BOXMAX = 31;
        static const int INDEXMAX = 30;
        static const int POKEMONNUMBER = 721;
        
        Savefile();
        
        void getPkmn(const int boxnumber, const int indexnumber, char* pkmn);
        bool getPkmn(std::string path, char* destination);
        std::string getBoxName(const int boxnumber);
        void setPkmn(const int boxnumber, const int indexnumber, char* pkmn);
        bool setPkmn(std::string path, char* source);
        bool writeSaveFile();
        int loadSaveFile();
        int writeSaveFileBackup(std::string path);
        std::wstring getTrainerName();
        
        virtual ~Savefile();
};

#endif /* SAVEFILE_H */

