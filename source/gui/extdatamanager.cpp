#include <cstring>

#include "extdatamanager.h"
#include "filesystem.h"
#include "compileoptions.h"
#include "inputmanager.h"
#include "state.h"

Savefile* ExtDataManager::saveptr = nullptr;
std::vector<std::string> ExtDataManager::guitext;
std::vector<u8> ExtDataManager::leveldata;
std::vector<u8> ExtDataManager::hpdata;
std::vector<u8> ExtDataManager::atkdata;
std::vector<u8> ExtDataManager::defdata;
std::vector<u8> ExtDataManager::spedata;
std::vector<u8> ExtDataManager::spadata;
std::vector<u8> ExtDataManager::spddata;
std::vector<u16> ExtDataManager::formdata;
std::vector<u8> ExtDataManager::numberformdata;
std::vector<u16> ExtDataManager::spriteformdata;
std::vector<std::string> ExtDataManager::species;
std::vector<std::string> ExtDataManager::natures;
std::vector<std::string> ExtDataManager::abilities;
std::vector<std::string> ExtDataManager::items;
std::vector<std::string> ExtDataManager::balls;
std::vector<std::string> ExtDataManager::moves;
std::vector<std::string> ExtDataManager::types;
std::vector<ExtDataManager::abilityset> ExtDataManager::abilitydata;

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
        langpath = "/en";
    
    else if( language == FRENCH )
        langpath = "/fr";
    
    else if( language == DEUTSCH )
        langpath = "/de";
        
    else if( language == ITALIAN )
        langpath = "/it";
    
    else if( language == SPANISH )
        langpath = "/es";
   
    else if( language == NEDERLAND )
        langpath = "/nl";
    
    else langpath = "/en";
    
    std::string path = getBasePath() + langpath;
    
    if( FileSystem::loadTextFile(path+"/guitext", guitext) != 0 )
        return 0x312;
    
    char* buffer = new char[0x11170];
    std::string personalpath;
    int count;
    int size;
    
    if( FileSystem::getGame() == FileSystem::XY) { personalpath = "/personal_xy"; count = 799; size = 0x40; }
    if( FileSystem::getGame() == FileSystem::ORAS) { personalpath = "/personal_ao"; count = 826; size = 0x50; }
    
    if( FileSystem::readFile(getBasePath()+personalpath, buffer) != 0 )
        return 0x313;
    
    //retrieve level type
    for(int i = 0; i < count; i++) {
        u8 toinsert;
        memcpy(&toinsert, &buffer[(i*size)+0x15], 1);
        leveldata.push_back(toinsert);
    }
    
    //retrieve hp base
    for(int i = 0; i < count; i++) {
        u8 toinsert;
        memcpy(&toinsert, &buffer[i*size], 1);
        hpdata.push_back(toinsert);
    }
    
    //retrieve atk base
    for(int i = 0; i < count; i++) {
        u8 toinsert;
        memcpy(&toinsert, &buffer[(i*size)+0x1], 1);
        atkdata.push_back(toinsert);
    }
    
    //retrieve def base
    for(int i = 0; i < count; i++) {
        u8 toinsert;
        memcpy(&toinsert, &buffer[(i*size)+0x2], 1);
        defdata.push_back(toinsert);
    }
    
    //retrieve spe base
    for(int i = 0; i < count; i++) {
        u8 toinsert;
        memcpy(&toinsert, &buffer[(i*size)+0x3], 1);
        spedata.push_back(toinsert);
    }
    
    //retrieve spa base
    for(int i = 0; i < count; i++) {
        u8 toinsert;
        memcpy(&toinsert, &buffer[(i*size)+0x4], 1);
        spadata.push_back(toinsert);
    }
    
    //retrieve spd base
    for(int i = 0; i < count; i++) {
        u8 toinsert;
        memcpy(&toinsert, &buffer[(i*size)+0x5], 1);
        spddata.push_back(toinsert);
    }
    
    //retrieve form number data
    for(int i = 0; i < count; i++) {
        u8 toinsert;
        memcpy(&toinsert, &buffer[(i*size)+0x20], 1);
        toinsert = toinsert-1;
        numberformdata.push_back(toinsert);
    }
    
    //retrieve form data UNSURE
    for(int i = 0; i < count; i++) {
        u8 toinsert;
        memcpy(&toinsert, &buffer[(i*size)+0x1C], 2);
        formdata.push_back(toinsert);
    }
    
    //retrieve sprite form data
    
    //Tricky and really unefficient workaround for the spritesheet bug
    char* buffer2 = new char[0x11170];
    if( FileSystem::getGame() == FileSystem::XY ) {
        if( FileSystem::readFile(getBasePath()+"/personal_ao", buffer2) != 0 )
            return 0x313;
    }
    
    else memcpy(buffer2, buffer, 0x11170);
    
    for(int i = 0; i < 826; i++) {
        u16 toinsert;
        memcpy(&toinsert, &buffer2[(i*0x50)+0x1E], 2);
        spriteformdata.push_back(toinsert);
    }
    
    //retrieve ability data
    for(int i = 0; i < count; i++) {
        abilityset setinsert;
        for(int j = 0; j < 3; j++) {
            u8 toinsert;
            memcpy(&toinsert, &buffer[(i*size)+(0x18+j)], 1);
            setinsert.push_back(toinsert);
        }
        
        abilitydata.push_back(setinsert);
    }
    
        
    if( FileSystem::loadTextFile(path+"/species", species) != 0 )
        return 0x314;
    
    if( FileSystem::loadTextFile(path+"/natures", natures) != 0 )
        return 0x315;
    
    if( FileSystem::loadTextFile(path+"/abilities", abilities) != 0 )
        return 0x316;
    
    if( FileSystem::loadTextFile(path+"/items", items) != 0 )
        return 0x317;
    
    if( FileSystem::loadTextFile(path+"/balls", balls) != 0 )
        return 0x318;
    
    if( FileSystem::loadTextFile(path+"/moves", moves) != 0 )
        return 0x319;
    
    if( FileSystem::loadTextFile(path+"/types", types) != 0 )
        return 0x320;
    
#ifdef __3dsx
    InputManager::scanInput();
    if( InputManager::isPressed(InputManager::BUTTON_SELECT) )
        State::setShoulderless(true);
#endif
    
    delete [] buffer;
    delete [] buffer2;
    return 0;
}
