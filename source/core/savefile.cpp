#include <cstring>
#include <3ds.h>

#include "savefile.h"
#include "filesystem.h"

Savefile::Savefile() {
    save = new char[0xEB000];
}

u32 Savefile::getCHKOffset(const int index) {
    u32 startoras[] = { 0x05400, 0x05800, 0x06400, 0x06600, 0x06800, 0x06A00, 0x06C00, 0x06E00, 0x07000, 0x07200, 0x07400, 0x09600, 0x09800, 0x09E00, 0x0A400, 0x0F400, 0x14400, 0x19400, 0x19600, 0x19E00, 0x1A400, 0x1B600, 0x1BE00, 0x1C000, 0x1C200, 0x1C800, 0x1CA00, 0x1CE00, 0x1D600, 0x1D800, 0x1DA00, 0x1DC00, 0x1DE00, 0x1E000, 0x1E800, 0x1EE00, 0x1F200, 0x20E00, 0x21000, 0x21400, 0x21800, 0x22000, 0x23C00, 0x24000, 0x24800, 0x24C00, 0x25600, 0x25A00, 0x26200, 0x27000, 0x27200, 0x27400, 0x28200, 0x28A00, 0x28E00, 0x30A00, 0x38400, 0x6D000, };
    u32 startxy[] = { 0x05400, 0x05800, 0x06400, 0x06600, 0x06800, 0x06A00, 0x06C00, 0x06E00, 0x07000, 0x07200, 0x07400, 0x09600, 0x09800, 0x09E00, 0x0A400, 0x0F400, 0x14400, 0x19400, 0x19600, 0x19E00, 0x1A400, 0x1AC00, 0x1B400, 0x1B600, 0x1B800, 0x1BE00, 0x1C000, 0x1C400, 0x1CC00, 0x1CE00, 0x1D000, 0x1D200, 0x1D400, 0x1D600, 0x1DE00, 0x1E400, 0x1E800, 0x20400, 0x20600, 0x20800, 0x20C00, 0x21000, 0x22C00, 0x23000, 0x23800, 0x23C00, 0x24600, 0x24A00, 0x25200, 0x26000, 0x26200, 0x26400, 0x27200, 0x27A00, 0x5C600, };
    
    if( FileSystem::getGame() == FileSystem::ORAS ) return startoras[index] - OFFSET;
    else if( FileSystem::getGame() == FileSystem::XY ) return startxy[index] - OFFSET;
    
    return 0;
}

u32 Savefile::getCHKLenght(const int index) {
    u32 lengthoras[] = { 0x000002C8, 0x00000B90, 0x0000002C, 0x00000038, 0x00000150, 0x00000004, 0x00000008, 0x000001C0, 0x000000BE, 0x00000024, 0x00002100, 0x00000130, 0x00000440, 0x00000574, 0x00004E28, 0x00004E28, 0x00004E28, 0x00000170, 0x0000061C, 0x00000504, 0x000011CC, 0x00000644, 0x00000104, 0x00000004, 0x00000420, 0x00000064, 0x000003F0, 0x0000070C, 0x00000180, 0x00000004, 0x0000000C, 0x00000048, 0x00000054, 0x00000644, 0x000005C8, 0x000002F8, 0x00001B40, 0x000001F4, 0x000003E0, 0x00000216, 0x00000640, 0x00001A90, 0x00000400, 0x00000618, 0x0000025C, 0x00000834, 0x00000318, 0x000007D0, 0x00000C48, 0x00000078, 0x00000200, 0x00000C84, 0x00000628, 0x00000400, 0x00007AD0, 0x000078B0, 0x00034AD0, 0x0000E058, };
    u32 lengthxy[] = { 0x000002C8, 0x00000B88, 0x0000002C, 0x00000038, 0x00000150, 0x00000004, 0x00000008, 0x000001C0, 0x000000BE, 0x00000024, 0x00002100, 0x00000140, 0x00000440, 0x00000574, 0x00004E28, 0x00004E28, 0x00004E28, 0x00000170, 0x0000061C, 0x00000504, 0x000006A0, 0x00000644, 0x00000104, 0x00000004, 0x00000420, 0x00000064, 0x000003F0, 0x0000070C, 0x00000180, 0x00000004, 0x0000000C, 0x00000048, 0x00000054, 0x00000644, 0x000005C8, 0x000002F8, 0x00001B40, 0x000001F4, 0x000001F0, 0x00000216, 0x00000390, 0x00001A90, 0x00000308, 0x00000618, 0x0000025C, 0x00000834, 0x00000318, 0x000007D0, 0x00000C48, 0x00000078, 0x00000200, 0x00000C84, 0x00000628, 0x00034AD0, 0x0000E058, };
    
    if(FileSystem::getGame() == FileSystem::ORAS) return lengthoras[index];
    if(FileSystem::getGame() == FileSystem::XY) return lengthxy[index];
    
    return 0;
}

u16 Savefile::ccitt16(char* data, const int size) {
  u16 crc = 0xFFFF;
  
  for (int i = 0; i < size; i++) {
    crc ^= (u16)data[i] << 8;
    for (int j = 0; j < 8; j++)
        if (crc & 0x8000)
            crc = crc << 1 ^ 0x1021;
        else
            crc = crc << 1;
    }
  
    return crc;
}

void Savefile::calculateChecksum() {
    int blocknumber;
    if( FileSystem::getGame() == FileSystem::ORAS ) blocknumber = 58;
    if( FileSystem::getGame() == FileSystem::XY ) blocknumber = 55;
    
    int checksumpos;
    if( FileSystem::getGame() == FileSystem::ORAS ) checksumpos = 0x7B21A - OFFSET;
    if( FileSystem::getGame() == FileSystem::XY ) checksumpos = 0x6A81A - OFFSET;
    
    char* temp = new char[0x35000];
    u16 checksum;
    
    for(int i = 0; i < blocknumber; i++) {
        memcpy(temp, &save[getCHKOffset(i)], getCHKLenght(i));
        checksum = ccitt16(temp, getCHKLenght(i));
        memcpy(&save[checksumpos + (i*8)], &checksum, 2);
    }
    
    delete [] temp;
}

u32 Savefile::seedStep(const u32 seed) {
    return (seed*0x41C64E6D + 0x00006073) & 0xFFFFFFFF;
}

void Savefile::shuffleArray(char* pkmn, const u32 encryptionkey) {
    const int BLOCKLENGHT = 56;
    
    u8 seed = (((encryptionkey & 0x3E000) >> 0xD) % 24);
    
    int aloc[24] = { 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3 };
    int bloc[24] = { 1, 1, 2, 3, 2, 3, 0, 0, 0, 0, 0, 0, 2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2 };
    int cloc[24] = { 2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2, 0, 0, 0, 0, 0, 0, 3, 2, 3, 2, 1, 1 };
    int dloc[24] = { 3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 3, 2, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0 };
    int ord[4] = {aloc[seed], bloc[seed], cloc[seed], dloc[seed]};
    
    char pkmncpy[PKMNLENGTH];
    char tmp[BLOCKLENGHT];

    memcpy(&pkmncpy, pkmn, PKMNLENGTH);
    
    for (int i = 0; i < 4; i++) {
        memcpy(tmp, pkmncpy + 8 + BLOCKLENGHT * ord[i], BLOCKLENGHT);
        memcpy(pkmn + 8 + BLOCKLENGHT * i, tmp, 56);
    }
}

void Savefile::decryptPkmn(char* pkmn) {
    const int ENCRYPTIONKEYPOS = 0x0;
    const int ENCRYPTIONKEYLENGHT = 4;
    const int CRYPTEDAREAPOS = 0x08;
    
    u32 encryptionkey;
    memcpy(&encryptionkey, &pkmn[ENCRYPTIONKEYPOS], ENCRYPTIONKEYLENGHT);
    u32 seed = encryptionkey;
    
    u16 temp;
    for(int i = CRYPTEDAREAPOS; i < PKMNLENGTH; i = i+2) {
        memcpy(&temp, &pkmn[i], 2);
        temp ^= (seedStep(seed) >> 16);
        seed = seedStep(seed);
        memcpy(&pkmn[i], &temp, 2);
    }
    
    shuffleArray(pkmn, encryptionkey);
}

int Savefile::getPkmnAddress(const int boxnumber, const int indexnumber) {
    int boxpos;
    if(FileSystem::getGame() == FileSystem::XY) boxpos = 0x27A00 - OFFSET;
    if(FileSystem::getGame() == FileSystem::ORAS) boxpos = 0x38400 - OFFSET;
    
    const int PKMNNUM = 30;
    
    return boxpos + (PKMNLENGTH * PKMNNUM * boxnumber) + (indexnumber * PKMNLENGTH);
}

void Savefile::calculatePKMNChecksum(char* data) {
    u16 chk = 0;

    for (int i = 8; i < 232; i += 2)
        chk += *(u16*)(data + i);
    
    memcpy(data + 6, &chk, 2);
}

void Savefile::encryptPkmn(char* pkmn) {
    const int ENCRYPTIONKEYPOS = 0x0;
    const int ENCRYPTIONKEYLENGHT = 4;
    const int CRYPTEDAREAPOS = 0x08;
    
    u32 encryptionkey;
    memcpy(&encryptionkey, &pkmn[ENCRYPTIONKEYPOS], ENCRYPTIONKEYLENGHT);
    u32 seed = encryptionkey;
    
    for(int i = 0; i < 11; i++)
        shuffleArray(pkmn, encryptionkey);
        
    u16 temp;
    for(int i = CRYPTEDAREAPOS; i < PKMNLENGTH; i = i+2) {
        memcpy(&temp, &pkmn[i], 2);
        temp ^= (seedStep(seed) >> 16);
        seed = seedStep(seed);
        memcpy(&pkmn[i], &temp, 2);
    }
}

void Savefile::getPkmn(const int boxnumber, const int indexnumber, char* pkmn) {
    memcpy(pkmn, &save[getPkmnAddress(boxnumber, indexnumber)], PKMNLENGTH);
    decryptPkmn(pkmn);
}

bool Savefile::getPkmn(std::string path, char* destination) {
    return FileSystem::readFile(path, destination);
}
 
void Savefile::setPkmn(const int boxnumber, const int indexnumber, char* pkmn) {
    calculatePKMNChecksum(pkmn);
    encryptPkmn(pkmn);
    memcpy(&save[getPkmnAddress(boxnumber, indexnumber)], pkmn, PKMNLENGTH);
}

bool Savefile::setPkmn(std::string path, char* source) {
    return FileSystem::writeFile(path, source, PKMNLENGTH);
}

bool Savefile::writeSaveFile() {
    calculateChecksum();
    if( FileSystem::writeSaveFile(save) != 0 )
        return 0x421;
    
    return 0;
}

int Savefile::loadSaveFile() {
    if( FileSystem::readSaveFile(save) != 0 )
        return 0x411;
    
    return 0;
}

int Savefile::writeSaveFileBackup(std::string path) {
    if( FileSystem::backupSaveFile(path, save) != 0 )
        return 0x422;
    
    return 0;
}

std::wstring Savefile::getTrainerName() {
    const int TRAINERNAMEADDRESS = 0x1C548 - OFFSET;
    const int TRAINERNAMELENGTH = 0x1C;
    
    u16 buffer[TRAINERNAMELENGTH/2];
    memcpy(buffer, &save[TRAINERNAMEADDRESS], TRAINERNAMELENGTH);
    uint32_t nkname[TRAINERNAMELENGTH/2];
    int length = utf16_to_utf32(nkname, buffer, TRAINERNAMELENGTH/2);
    nkname[length] = 0x0;
    std::wstring nickname((wchar_t*)nkname);
    return nickname;
}

Savefile::~Savefile() {
   delete [] save;
}