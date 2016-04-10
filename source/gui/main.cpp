#include "graphic.h"
#include "filesystem.h"
#include "savefile.h"
#include "extdatamanager.h"
#include "gui.h"
#include "state.h"
#include "pokemon.h"
#include "compileoptions.h"

int main() {
    //ENVIROMENT INITIALIZATION
    int game = 0;
    int mediatype = 0;
    int res;
    int err = 0;
    
    //Graphic enviroment initialization
    Graphic::startGraphicEnviroment();

    //Savefile loading
#ifdef __cia
    FileSystem::romFsInit();
    ciaConsole(game, mediatype);
#endif
    
    //Loading screen
    //loadingScreen();
    
    //Filesystem initialization
    res = FileSystem::initialize(game, mediatype);
    if( res != 0 )
        err = res;
    
    Savefile save;
    res = save.loadSaveFile();
    if( res != 0 )
        err = res;
    
    //ExtData Initialization
    res = ExtDataManager::initialize(&save);
    if( res != 0 )
        err = res;

    //Savefile backup
    const std::string BACKUPPATH = "/pk/PCHex++/backup/main";
    res = ExtDataManager::getSave()->writeSaveFileBackup(BACKUPPATH);
    if( res != 0 )
        err = res;
    
    //Managing initialization error
    if( err != 0 )
        initializationError(err);
    
    //MAIN LOOP
    while(State::getMode() != State::EXITMODE) {
        inputHandler();
        
        drawTopScreen();
        drawBottomScreen();
        Graphic::swapbuffer();
    }
    
    //ENVIROMENT CLEANING
    FileSystem::closeFileSystem();
    Graphic::closeGraphicEnviroment();
    return 0;
}