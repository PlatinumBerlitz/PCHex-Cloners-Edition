#include "graphic.h"
#include "filesystem.h"
#include "savefile.h"
#include "extdatamanager.h"
#include "gui.h"
#include "state.h"
#include "pokemon.h"
#include "compileoptions.h"

int main() {
    int game = 0;
    int mediatype = 0;
    int res;
    int err = 0;
    
    //Graphic enviroment initialization
    Graphic::startGraphicEnviroment();
    
    //Filesystem initialization
    res = FileSystem::initialize(game, mediatype);
    if( res != 0 )
        err = res;
    
    //Savefile loading
#ifdef __cia
    ciaConsole(game, mediatype);
#endif

    Savefile save;
    res = save.loadSaveFile();
    if( res != 0 )
        err = res;
    
    //ExtData Initialization
    res = ExtDataManager::initialize(&save);
    if( res != 0 )
        err = res;

    if( err != 0 )
        initializationError(err);
    
    while(State::getMode() != State::EXITMODE) {
        inputHandler();
        
        drawTopScreen();
        Graphic::swapbuffer();
    }
    
    FileSystem::closeFileSystem();
    Graphic::closeGraphicEnviroment();
    return 0;
}