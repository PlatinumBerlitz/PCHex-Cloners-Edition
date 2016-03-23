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
#include "compileoptions.h"
#include "button.h"
#include "pokemon.h"
#include "overlay.h"
#include "editableoverlay.h"

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
        
        Text versiontext(FontManager::getFont(fontpath), 15, 15, 9, Text::WHITE, VERSIONNUMBER);
        versiontext.draw();
        
        Text errtext(FontManager::getFont(fontpath), 15, 25, 9, Text::WHITE, "Initialization Error:");
        errtext.draw();
        
        Text numerrtext(FontManager::getFont(fontpath), 90, 25, 9, Text::WHITE, intTOstring(err, 16));
        numerrtext.draw();
        
        Text starttext(FontManager::getFont(fontpath), 15, 35, 9, Text::WHITE, "Press START to exit.");
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
        
        else if( State::getMode() == State::EDITABLEOVERLAYMODE )
            State::setEovSelected(State::getEovSelected()+1);
    }
    
    //UP KEY
    if( InputManager::isPressed(InputManager::BUTTON_UP) ) {
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::CLONEMODE )
            State::setIndexNumber(State::getIndexNumber()-3);
        
        else if( State::getMode() == State::EDITABLEOVERLAYMODE )
            State::setEovSelected(State::getEovSelected()-1);
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
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLESELECTMODE || State::getMode() == State::MULTIPLECLONEMODE )
            changeBox(State::getBoxNumber()-1);
    }
    
    //R KEY
    if( InputManager::isPressed(InputManager::BUTTON_R) ) {
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLESELECTMODE || State::getMode() == State::MULTIPLECLONEMODE )
            changeBox(State::getBoxNumber()+1);
    }
    
    //X KEY
    if( InputManager::isPressed(InputManager::BUTTON_X) ) {
        if( State::getMode() == State::SELECTMODE )
            selectClone();
        
        else if( State::getMode() == State::MULTIPLESELECTMODE )
            multipleSelectClone();
    }
    
    //B KEY
    if( InputManager::isPressed(InputManager::BUTTON_B) ) {
        if( State::getMode() == State::CLONEMODE )
            State::setMode(State::SELECTMODE);
        
        else if( State::getMode() == State::MULTIPLESELECTMODE || State::getMode() == State::MULTIPLECLONEMODE)
            State::setMode(State::SELECTMODE);
    }
    
    //A KEY
    if( InputManager::isPressed(InputManager::BUTTON_A) ) {
        if( State::getMode() == State::CLONEMODE )
            clone();
        
        else if( State::getMode() == State::OVERLAYMODE )
            State::setMode(State::getBackupMode());
        
        else if( State::getMode() == State::MULTIPLECLONEMODE )
            multipleClone();
    }
    
    //Y KEY
    if( InputManager::isPressed(InputManager::BUTTON_Y) ) {
        if( State::getMode() == State::SELECTMODE )
            selectImport();
    }
    
    //SELECT KEY
    if( InputManager::isPressed(InputManager::BUTTON_SELECT) ) {
        if( State::getMode() == State::SELECTMODE )
            State::setMode(State::MULTIPLESELECTMODE);
    }
}

void drawTopScreen() {
    const std::string ROBOTOBOLDPATH = ExtDataManager::getBasePath() + "/fonts/roboto_bold.ttf";
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
    
    //Draw box info
    const std::string BOXINFOPATH = ExtDataManager::getBasePath() + "/textures/boxinfo.png";
    const int XBOXINFOSTART = (Graphic::TOPSCREENWIDTH/2) - (TextureManager::getTexture(BOXINFOPATH)->width/2);
    const int YBOXINFOSTART = 0;
    Drawable* boxinfo = new Drawable(TextureManager::getTexture(BOXINFOPATH), XBOXINFOSTART, YBOXINFOSTART);
    topelements.push_back(boxinfo);
    
    const std::string BOXNUMBERSTRING = ExtDataManager::getGuiText(ExtDataManager::BOXSTRING) + " " + intTOstring(State::getBoxNumber()+1, 10);
    const int XBOXINFOTEXTSTART = XBOXINFOSTART + (TextureManager::getTexture(BOXINFOPATH)->width/2) - (getTextWidth(FontManager::getFont(ROBOTOBOLDPATH), 9, BOXNUMBERSTRING)/2);
    const int YBOXINFOTEXTSTART = YBOXINFOSTART + 7;
    Text* boxnumber = new Text(FontManager::getFont(ROBOTOBOLDPATH), XBOXINFOTEXTSTART, YBOXINFOTEXTSTART, 9, Text::WHITE, BOXNUMBERSTRING);
    topelements.push_back(boxnumber);
    
    //Draw shoulder button
    //L
    int lnumber = State::getBoxNumber();
    if( lnumber == 0)
        lnumber = 31;
    
    const std::string LBUTTONPATH = ExtDataManager::getBasePath() + "/textures/lboxinfo.png";
    const int XLBUTTONSTART = 0;
    const int YLBUTTONSTART = 0;
    Button* lbutton = new Button(TextureManager::getTexture(LBUTTONPATH), XLBUTTONSTART, YLBUTTONSTART, InputManager::BUTTON_L, ExtDataManager::getGuiText(ExtDataManager::BOXSTRING) + " " + intTOstring(lnumber, 10));
    topelements.push_back(lbutton);
    
    int rnumber = State::getBoxNumber() + 2;
    if(rnumber == 32)
        rnumber = 1;
    
    //R 
    const std::string RBUTTONPATH = ExtDataManager::getBasePath() + "/textures/rboxinfo.png";
    const int XRBUTTONSTART = Graphic::TOPSCREENWIDTH - TextureManager::getTexture(RBUTTONPATH)->width;
    const int YRBUTTONSTART = 0; 
    Button* rbutton = new Button(TextureManager::getTexture(RBUTTONPATH), XRBUTTONSTART, YRBUTTONSTART, InputManager::BUTTON_R, ExtDataManager::getGuiText(ExtDataManager::BOXSTRING) + " " + intTOstring(rnumber, 10));
    topelements.push_back(rbutton);
    
    //Draw bottom button area
    const int BUTTONDISTANCE = 25;
    //Center
    const std::string CENTERBUTTONPATH = ExtDataManager::getBasePath() + "/textures/orangebutton.png";
    const int XCENTERBUTTONSTART = (Graphic::TOPSCREENWIDTH/2) - (TextureManager::getTexture(CENTERBUTTONPATH)->width/2);
    if( State::getMode() == State::SELECTMODE || State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLESELECTMODE || State::getMode() == State::MULTIPLECLONEMODE ) {
        if( State::getMode() == State::SELECTMODE ) {
            const int YCENTERBUTTONSTART = Graphic::TOPSCREENHEIGHT - TextureManager::getTexture(CENTERBUTTONPATH)->height;
            Button* centerbutton = new Button(TextureManager::getTexture(CENTERBUTTONPATH), XCENTERBUTTONSTART, YCENTERBUTTONSTART, InputManager::BUTTON_A, ExtDataManager::getGuiText(ExtDataManager::EDITSTRING));
            topelements.push_back(centerbutton);
        }

        //Left
        const std::string LEFTBUTTONPATH = ExtDataManager::getBasePath() + "/textures/bluebutton.png";
        const int XLEFTBUTTONSTART = XCENTERBUTTONSTART - TextureManager::getTexture(LEFTBUTTONPATH)->width - BUTTONDISTANCE;
        const int YLEFTBUTTONSTART = Graphic::TOPSCREENHEIGHT - TextureManager::getTexture(LEFTBUTTONPATH)->height;

        std::string leftmsg;
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::MULTIPLESELECTMODE ) leftmsg = ExtDataManager::getGuiText(ExtDataManager::IMPORTSTRING);
        else if ( State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLECLONEMODE ) leftmsg = ExtDataManager::getGuiText(ExtDataManager::CANCELSTRING);

        int lefticon;
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::MULTIPLESELECTMODE ) lefticon = InputManager::BUTTON_Y;
        else if ( State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLECLONEMODE ) lefticon = InputManager::BUTTON_B;

        Button* leftbutton = new Button(TextureManager::getTexture(LEFTBUTTONPATH), XLEFTBUTTONSTART, YLEFTBUTTONSTART, lefticon, leftmsg);
        topelements.push_back(leftbutton);

        //Right
        const std::string RIGHTBUTTONPATH = ExtDataManager::getBasePath() + "/textures/greenbutton.png";
        const int XRIGHTBUTTONSTART = XCENTERBUTTONSTART + TextureManager::getTexture(LEFTBUTTONPATH)->width + BUTTONDISTANCE;
        const int YRIGHTBUTTONSTART = Graphic::TOPSCREENHEIGHT - TextureManager::getTexture(RIGHTBUTTONPATH)->height;

        std::string rightmsg;
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::MULTIPLESELECTMODE ) rightmsg = ExtDataManager::getGuiText(ExtDataManager::CLONESTRING);
        else if ( State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLECLONEMODE ) rightmsg = ExtDataManager::getGuiText(ExtDataManager::CHOOSESTRING);

        int righticon;
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::MULTIPLESELECTMODE) righticon = InputManager::BUTTON_X;
        else if ( State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLECLONEMODE ) righticon = InputManager::BUTTON_A;

        Button* rightbutton = new Button(TextureManager::getTexture(RIGHTBUTTONPATH), XRIGHTBUTTONSTART, YRIGHTBUTTONSTART, righticon, rightmsg);
        topelements.push_back(rightbutton);
    }
    
    //Draw center screen message
    std::string centerscreenmsg;
    if( State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLECLONEMODE ) centerscreenmsg = ExtDataManager::getGuiText(ExtDataManager::SELECTCLONINGSTRING);
    if( State::getMode() == State::MULTIPLESELECTMODE ) centerscreenmsg = ExtDataManager::getGuiText(ExtDataManager::MULTIPLESELECTSTRING);
    Text* centerscreentxt;
    const int XCENTERSCREENMSGSTART = (Graphic::TOPSCREENWIDTH/2) - (getTextWidth(FontManager::getFont(ROBOTOBOLDPATH), 9, centerscreenmsg)/2);
    const int YCENTERSCREENMSGSTART = Graphic::TOPSCREENHEIGHT - 15;
    if( State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLESELECTMODE || State::getMode() == State::MULTIPLECLONEMODE ){ 
        centerscreentxt = new Text(FontManager::getFont(ROBOTOBOLDPATH), XCENTERSCREENMSGSTART, YCENTERSCREENMSGSTART, 9, Text::BLACK, centerscreenmsg);
        topelements.push_back(centerscreentxt);
    }
    
    //Draw overlay
    Overlay* ov;
    if( State::getMode() == State::OVERLAYMODE ) {
        const std::string OVERLAYPATH = ExtDataManager::getBasePath() + "/textures/overlay.png";
        ov = new Overlay(TextureManager::getTexture(OVERLAYPATH), State::getOverlayMsg());
        topelements.push_back(ov);
    }
    
    //Draw editable overlay
    EditableOverlay* eov;
    if( State::getMode() == State::EDITABLEOVERLAYMODE ) {
        const std::string EOVPATH = ExtDataManager::getBasePath() + "/textures/editableoverlay.png";
        eov = new EditableOverlay(TextureManager::getTexture(EOVPATH), State::getEovSelected(), State::getOverlayMsg(), State::getEovVector());
        topelements.push_back(eov);
    }
    
    //Draw version number
    const std::string VERSIONNUMBERSTRING = VERSIONNUMBER;
    const int XVERSIONNUMBERSTART = Graphic::TOPSCREENWIDTH - getTextWidth(FontManager::getFont(ROBOTOBOLDPATH), 9, VERSIONNUMBERSTRING) - 5;
    const int YVERSIONNUMBERSTART =  Graphic::TOPSCREENHEIGHT - 15;
    Text* versionnumber = new Text(FontManager::getFont(ROBOTOBOLDPATH), XVERSIONNUMBERSTART, YVERSIONNUMBERSTART, 9, Text::BLACK, VERSIONNUMBERSTRING);
    topelements.push_back(versionnumber);
    
    //polymorphic draw call
    for(unsigned int i = 0; i < topelements.size(); i++)
        topelements[i]->draw();
    
    //polymorphic delete call
    for(unsigned int i = 0; i < topelements.size(); i++)
        delete topelements[i];
    
    Graphic::endFrame();
}

void changeBox(const int val) {
    State::setBoxNumber(val);
    State::setIndexNumber(0);
}

void selectClone() {
    State::setCloneOrigin(State::getBoxNumber(), State::getIndexNumber());
    State::setMode(State::CLONEMODE);
}

void clone() {
    Pokemon toclone(State::getBoxCloneOrigin(), State::getIndexCloneOrigin(), ExtDataManager::getSave());
    if( toclone.clone(State::getBoxNumber(), State::getIndexNumber(), true) != 0 )
        State::setOverlayMsg(ExtDataManager::getGuiText(ExtDataManager::FAILEDSTRING));
    
    else State::setOverlayMsg(ExtDataManager::getGuiText(ExtDataManager::SUCCESSSSTRING));
    
    State::setBackupMode(State::SELECTMODE);
    
    State::setMode(State::OVERLAYMODE);
}

void multipleSelectClone() {
    State::setCloneOrigin(State::getBoxNumber(), State::getIndexNumber());
    State::setMode(State::MULTIPLECLONEMODE);
}

void multipleClone() {
    for(int i = 0; i < 30; i++) {
        Pokemon toclone(State::getBoxCloneOrigin(), i, ExtDataManager::getSave());
        toclone.clone(State::getBoxNumber(), i, false);
    }
    
    if( ExtDataManager::getSave()->writeSaveFile() != 0 )
        State::setOverlayMsg(ExtDataManager::getGuiText(ExtDataManager::FAILEDSTRING));
    
    else State::setOverlayMsg(ExtDataManager::getGuiText(ExtDataManager::SUCCESSSSTRING));
    
    State::setBackupMode(State::SELECTMODE);
    State::setMode(State::OVERLAYMODE);
}

void selectImport() {
    State::setEovMode(State::IMPORTEOV);
    State::setOverlayMsg(ExtDataManager::getGuiText(ExtDataManager::SELECTPK6STRING));
    State::setEovVector(ExtDataManager::getSpeciesNameVector());
    State::setMode(State::EDITABLEOVERLAYMODE);
}