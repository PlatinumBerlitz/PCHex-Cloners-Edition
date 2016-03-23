#include <cstring>

#include "extdatamanager.h"
#include "filesystem.h"
#include "compileoptions.h"

Savefile* ExtDataManager::saveptr = nullptr;
std::vector<std::string> ExtDataManager::guitext;
std::vector<u8> ExtDataManager::leveldata;
std::vector<std::string> ExtDataManager::species;

std::string ExtDataManager::getBasePath() {
#ifdef __cia
    return "romfs:";
#else
    return "/3ds/PCHex++/romfs";
#endif
}

int ExtDataManager::initialize(Savefile* save) {
    saveptr = save;
    FileSystem::createDirectory("/pk");
    FileSystem::createDirectory("/pk/PCHex++");
    FileSystem::createDirectory("/pk/PCHex++/import");
    FileSystem::createDirectory("/pk/PCHex++/export");
    FileSystem::createDirectory("/pk/PCHex++/backup");
    
    cfguInit();
    u8 language;
    
    if( CFGU_GetSystemLanguage(&language) )
        return 0x311;
    
    std::string langpath;
    if( language == ENGLISH )
        langpath = "/eng";
    
    else langpath = "/eng";
    
    std::string path = getBasePath() + langpath;
    
    if( FileSystem::loadTextFile(path+"/guitext", guitext) != 0 )
        return 0x312;
    
    char buffer[0x32c8];
    if( FileSystem::readFile(path+"/personal", buffer) != 0 )
        return 0x313;
    
    for(int i = 0; i < 826; i++) {
        u8 toinsert;
        memcpy(&toinsert, &buffer[(i*14)+11], 1);
        leveldata.push_back(toinsert);
    }
    
    if( FileSystem::loadTextFile(path+"/species", species) != 0 )
        return 0x314;
    
    return 0;
}
