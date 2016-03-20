#include <3ds.h>
#include <vector>
#include <string>

#include "gui.h"
#include "extdatamanager.h"
#include "inputmanager.h"
#include "graphic.h"
#include "text.h"
#include "fontmanager.h"
#include "state.h"
#include "box.h"
#include "filesystem.h"
#include "utility.h"

void ciaConsole(int& game, int& mediatype) {
    bool exit = false;
    std::vector<std::string> entries;
    entries.push_back("Pokemon Cartridge");
    entries.push_back("Pokemon X Digital Copy");
    entries.push_back("Pokemon Y Digital Copy");
    entries.push_back("Pokemon Omega Ruby Digital Copy");
    entries.push_back("Pokemon Alpha Sapphire Digital Copy");

    while(!exit) {
        std::vector<Drawable*> elements;
        InputManager::scanInput();
        if( InputManager::isPressed(InputManager::BUTTON_A) )
            exit = true;
        
        if( InputManager::isPressed(InputManager::BUTTON_DOWN) )
            State::setCiaSelected(State::getCiaSelected()+1);
        
        if( InputManager::isPressed(InputManager::BUTTON_UP) )
            State::setCiaSelected(State::getCiaSelected()-1);

        Graphic::startFrame(Graphic::BOTTOMSCREEN);
        
        const std::string fontpath = ExtDataManager::getBasePath() + "/fonts/roboto_bold.ttf";
        Text* selecttext = new Text(FontManager::getFont(fontpath), 15, 15, 9, Text::WHITE, "Select your game:");
        elements.push_back(selecttext);

        for(unsigned int i = 0; i < entries.size(); i++) {
            const int START = 30;
            const int DISTANCE = 12;
            int color;
            if( State::getCiaSelected() == i ) color = Text::RED;
            else color = Text::WHITE;
            
            Text* entry = new Text(FontManager::getFont(fontpath), 15, START+(DISTANCE*i), 9, color, entries[i]);
            elements.push_back(entry);
        }

        for(unsigned int i = 0; i < elements.size(); i++)
            elements[i]->draw();

        for(unsigned int i = 0; i < elements.size(); i++)
            delete elements[i];
        
        Graphic::endFrame();
        Graphic::swapbuffer();
    }
    
    if(State::getCiaSelected() == 0) {
        game = 0;
        mediatype = FileSystem::CART;
    }
    
    if(State::getCiaSelected() == 1) {
        game = FileSystem::X;
        mediatype = FileSystem::CIA;
    }
    
    if(State::getCiaSelected() == 2) {
        game = FileSystem::Y;
        mediatype = FileSystem::CIA;
    }
    
    if(State::getCiaSelected() == 3) {
        game = FileSystem::OR;
        mediatype = FileSystem::CIA;
    }
    
    if(State::getCiaSelected() == 4) {
        game = FileSystem::AS;
        mediatype = FileSystem::CIA;
    }
}

void initializationError(const int err) {
    bool exit = false;
    while(!exit) {
        InputManager::scanInput();
        if( InputManager::isPressed(InputManager::BUTTON_START) )
            exit = true;
        
        Graphic::startFrame(Graphic::TOPSCREEN);
        
        const std::string fontpath = ExtDataManager::getBasePath() + "/fonts/roboto_bold.ttf";
        Text errtext(FontManager::getFont(fontpath), 15, 15, 9, Text::WHITE, "Initialization Error:");
        errtext.draw();
        
        Text numerrtext(FontManager::getFont(fontpath), 90, 15, 9, Text::WHITE, intTOstring(err, 16));
        numerrtext.draw();
        
        Text starttext(FontManager::getFont(fontpath), 15, 25, 9, Text::WHITE, "Press START to exit.");
        starttext.draw();
        
        Graphic::endFrame();
        
        Graphic::swapbuffer();
    }
    
    State::setMode(State::EXITMODE);
}

void inputHandler() {
    InputManager::scanInput();
    
    //START KEY
    if( InputManager::isPressed(InputManager::BUTTON_START) ) {
        State::setMode(State::EXITMODE);
    }
    
    //DOWN KEY
    if( InputManager::isPressed(InputManager::BUTTON_DOWN) ) {
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::CLONEMODE )
            State::setIndexNumber(State::getIndexNumber()+3);
    }
    
    //UP KEY
    if( InputManager::isPressed(InputManager::BUTTON_UP) ) {
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::CLONEMODE )
            State::setIndexNumber(State::getIndexNumber()-3);
    }
    
    //RIGHT KEY
    if( InputManager::isPressed(InputManager::BUTTON_RIGHT) ) {
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::CLONEMODE )
            State::setIndexNumber(State::getIndexNumber()+1);
    }
    
    //LEFT KEY
    if( InputManager::isPressed(InputManager::BUTTON_LEFT) ) {
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::CLONEMODE )
            State::setIndexNumber(State::getIndexNumber()-1);
    }
    
    //L KEY
    if( InputManager::isPressed(InputManager::BUTTON_L) ) {
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::CLONEMODE )
            State::setBoxNumber(State::getBoxNumber()-1);
    }
    
    //R KEY
    if( InputManager::isPressed(InputManager::BUTTON_R) ) {
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::CLONEMODE )
            State::setBoxNumber(State::getBoxNumber()+1);
    }
}

void drawTopScreen() {
    std::vector<Drawable*> topelements;
    
    Graphic::startFrame(Graphic::TOPSCREEN);
    
    //Draw background
    const std::string BACKGROUNDPATH = ExtDataManager::getBasePath() + "/textures/background.png";
    Drawable* backgroundtexture = new Drawable(TextureManager::getTexture(BACKGROUNDPATH), 0, 0);
    topelements.push_back(backgroundtexture);
    
    //Draw box
    const int XBOXSTART = 15;
    const int YBOXSTART = 30;
    Box* box = new Box(XBOXSTART, YBOXSTART);
    topelements.push_back(box);
    
    //polymorphic draw call
    for(unsigned int i = 0; i < topelements.size(); i++)
        topelements[i]->draw();
    
    //polymorphic delete call
    for(unsigned int i = 0; i < topelements.size(); i++)
        delete topelements[i];
    
    Graphic::endFrame();
}