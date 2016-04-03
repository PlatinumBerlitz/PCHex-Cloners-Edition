#include <3ds.h>
#include <vector>
#include <string>
#include <algorithm>

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
#include "field.h"
#include "largebutton.h"
#include "multifield.h"

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
    Pokemon pika(State::getBoxNumber(), State::getIndexNumber(), ExtDataManager::getSave());
    
    
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
        
        else if( State::getMode() == State::EDITABLEOVERLAYMODE )
            State::setSkip(State::getSkip()-1);
    }
    
    //R KEY
    if( InputManager::isPressed(InputManager::BUTTON_R) ) {
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLESELECTMODE || State::getMode() == State::MULTIPLECLONEMODE )
            changeBox(State::getBoxNumber()+1);
        
        else if( State::getMode() == State::EDITABLEOVERLAYMODE )
            State::setSkip(State::getSkip()+1);
    }
    
    //X KEY
    if( InputManager::isPressed(InputManager::BUTTON_X) ) {
        if( State::getMode() == State::SELECTMODE )
            selectClone();
        
        else if( State::getMode() == State::MULTIPLESELECTMODE )
            multipleSelectClone();
    }
    
    //B KEY
    if( InputManager::isPressed(InputManager::BUTTON_B) || State::getKeyboardState() == 3 ) {
        if( State::getMode() == State::CLONEMODE )
            State::setMode(State::SELECTMODE);
        
        else if( State::getMode() == State::MULTIPLESELECTMODE || State::getMode() == State::MULTIPLECLONEMODE)
            State::setMode(State::SELECTMODE);
        
        else if( State::getMode() == State::EDITABLEOVERLAYMODE )
            closeEov();
        
        else if( State::getMode() == State::EDITMODE )
            cancelEdit();
    }
    
    //A KEY
    if( InputManager::isPressed(InputManager::BUTTON_A) || State::getKeyboardState() == 1 ) {
        if( State::getMode() == State::CLONEMODE )
            clone();
        
        else if( State::getMode() == State::OVERLAYMODE )
            State::setMode(State::getBackupMode());
        
        else if( State::getMode() == State::MULTIPLECLONEMODE )
            multipleClone();
        
        else if( State::getMode() == State::EDITABLEOVERLAYMODE && State::getEovMode() == State::IMPORTEOV )
            import();
        
        else if( State::getMode() == State::SELECTMODE && pika.getPokedexNumber() > 0 )
            startEdit();
        
        else if( State::getMode() == State::EDITABLEOVERLAYMODE && State::getEovMode() == State::NATUREEOV )
            editNature();
        
        else if( State::getMode() == State::EDITABLEOVERLAYMODE && State::getEovMode() == State::ABILITYEOV )
            editAbility();
        
        else if( State::getMode() == State::EDITABLEOVERLAYMODE && State::getEovMode() == State::ITEMEOV )
            editItem();
        
        else if( State::getMode() == State::EDITABLEOVERLAYMODE && State::getEovMode() == State::BALLEOV )
            editBall();
        
        else if( State::getMode() == State::EDITABLEOVERLAYMODE && State::getEovMode() == State::SPECIESEOV )
            editSpecies();
        
        else if( State::getMode() == State::EDITABLEOVERLAYMODE && State::getEovMode() >= State::MOVE1EOV && State::getEovMode() <= State::MOVE4EOV )
            editMove();
        
        else if( State::getMode() == State::EDITABLEOVERLAYMODE && State::getEovMode() >= State::EGGMOVE1EOV && State::getEovMode() <= State::EGGMOVE4EOV )
            editEggMove();
                
        else if( State::getMode() == State::EDITMODE )
            commitSave();
     }
    
    //Y KEY
    if( InputManager::isPressed(InputManager::BUTTON_Y) ) {
        if( State::getMode() == State::SELECTMODE )
            selectImport();
        
        else if( State::getMode() == State::EDITMODE )
            exprt();
    }
    
    //SELECT KEY
    if( InputManager::isPressed(InputManager::BUTTON_SELECT) ) {
        if( State::getMode() == State::SELECTMODE )
            State::setMode(State::MULTIPLESELECTMODE);
    }
    
    //Touch management
    const int BUTTONDELAY = 2;
    const int KEEPBUTTONDELAY = 20;
    
    if( State::getTouchId() == State::NATUREBUTTON )
        selectNature();
    
    if( State::getTouchId() == State::ABILITYBUTTON )
        selectAbility();
    
    if( State::getTouchId() == State::ITEMBUTTON )
        selectItem();
    
    if( State::getTouchId() == State::BALLBUTTON )
        selectBall();
    
    if( State::getTouchId() == State::SHINYBUTTON && State::getButtonDelay() > BUTTONDELAY )
        setShiny();
    
    if( State::getTouchId() == State::GENDERBUTTON && State::getButtonDelay() > BUTTONDELAY )
        setGender();
    
    if( State::getTouchId() == State::SPECIESBUTTON )
        selectSpecies();
    
    if( State::getTouchId() == State::LVBUTTONDOWN && (State::getButtonDelay() > BUTTONDELAY || State::getKeepButtonDelay() > KEEPBUTTONDELAY) && pika.getLevel() > 1 )
        pika.setLevel(pika.getLevel()-1);
     
    if( State::getTouchId() == State::LVBUTTONUP && (State::getButtonDelay() > BUTTONDELAY || State::getKeepButtonDelay() > KEEPBUTTONDELAY) && pika.getLevel() < 100 )
        pika.setLevel(pika.getLevel()+1);
    
    if( State::getTouchId() == State::TABBUTTON && State::getButtonDelay() > BUTTONDELAY )
        State::setTab(!State::getTab());
    
    if( State::getTouchId() >= State::MOVE1BUTTON && State::getTouchId() <= State::EGGMOVE4BUTTON )
        selectMove(State::getTouchId());
    
    if( State::getTouchId() >= State::HPIVBUTTONDOWN && State::getTouchId() <= State::SPDIVBUTTONDOWN && (State::getButtonDelay() > BUTTONDELAY || State::getKeepButtonDelay() > KEEPBUTTONDELAY) && pika.getIV(State::getTouchId()-State::HPIVBUTTONDOWN) > 0 )
        pika.setIV(pika.getIV(State::getTouchId()-State::HPIVBUTTONDOWN)-1, State::getTouchId()-State::HPIVBUTTONDOWN);
    
    if( State::getTouchId() >= State::HPIVBUTTONUP && State::getTouchId() <= State::SPDIVBUTTONUP && (State::getButtonDelay() > BUTTONDELAY || State::getKeepButtonDelay() > KEEPBUTTONDELAY) && pika.getIV(State::getTouchId()-State::HPIVBUTTONUP) < 31 )
        pika.setIV(pika.getIV(State::getTouchId()-State::HPIVBUTTONUP)+1, State::getTouchId()-State::HPIVBUTTONUP);
    
    if( State::getTouchId() >= State::HPEVBUTTONDOWN && State::getTouchId() <= State::SPDEVBUTTONDOWN && (State::getButtonDelay() > BUTTONDELAY || State::getKeepButtonDelay() > KEEPBUTTONDELAY) && pika.getEV(State::getTouchId()-State::HPEVBUTTONDOWN) > 0 )
        pika.setEV(pika.getEV(State::getTouchId()-State::HPEVBUTTONDOWN)-1, State::getTouchId()-State::HPEVBUTTONDOWN);
    
    if( State::getTouchId() >= State::HPEVBUTTONUP && State::getTouchId() <= State::SPDEVBUTTONUP && (State::getButtonDelay() > BUTTONDELAY || State::getKeepButtonDelay() > KEEPBUTTONDELAY) && pika.getEV(State::getTouchId()-State::HPEVBUTTONUP) < 255 && !pika.isEVMAX() )
        pika.setEV(pika.getEV(State::getTouchId()-State::HPEVBUTTONUP)+1, State::getTouchId()-State::HPEVBUTTONUP);
    
    
    //Keyboard management
        if( (State::getKeyboardState() == 2) || (InputManager::isPressed(InputManager::BUTTON_L) && State::getMode() == State::EDITABLEOVERLAYMODE && State::keyboard.HBKB_CheckKeyboardInput().size() > 0) || (InputManager::isPressed(InputManager::BUTTON_R) && State::getMode() == State::EDITABLEOVERLAYMODE && State::keyboard.HBKB_CheckKeyboardInput().size() > 0) ) 
            search();
    
    //Delay Management
    State::setButtonDelay(State::getButtonDelay()+1);
    if(State::getTouchId() > 0) {
        State::setButtonDelay(0);
        State::setKeepButtonDelay(State::getKeepButtonDelay()+1);
    }
    
    else State::setKeepButtonDelay(0);
    
    if(State::getMode() == State::EDITABLEOVERLAYMODE) 
        State::setKeyboardDelay(State::getKeyboardDelay()+1);
    
    else State::setKeyboardDelay(0);
    
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
    std::string lmessage;
    
    if( State::getMode() == State::EDITABLEOVERLAYMODE ) lmessage = ExtDataManager::getGuiText(ExtDataManager::PREVSTRING);
    else lmessage = ExtDataManager::getGuiText(ExtDataManager::BOXSTRING) + " " + intTOstring(lnumber, 10);
    
    Button* lbutton;
    if( State::getMode() != State::EDITMODE ) {
        lbutton = new Button(TextureManager::getTexture(LBUTTONPATH), XLBUTTONSTART, YLBUTTONSTART, InputManager::BUTTON_L, lmessage);
        topelements.push_back(lbutton);
    }
    
    
    //R
    int rnumber = State::getBoxNumber() + 2;
    if(rnumber == 32)
        rnumber = 1;
    
    const std::string RBUTTONPATH = ExtDataManager::getBasePath() + "/textures/rboxinfo.png";
    const int XRBUTTONSTART = Graphic::TOPSCREENWIDTH - TextureManager::getTexture(RBUTTONPATH)->width;
    const int YRBUTTONSTART = 0; 
    std::string rmessage;
    
    if( State::getMode() == State::EDITABLEOVERLAYMODE ) rmessage = ExtDataManager::getGuiText(ExtDataManager::NEXTSTRING);
    else rmessage = ExtDataManager::getGuiText(ExtDataManager::BOXSTRING) + " " + intTOstring(rnumber, 10);
    
    Button* rbutton;
    if( State::getMode() != State::EDITMODE ) {
        rbutton = new Button(TextureManager::getTexture(RBUTTONPATH), XRBUTTONSTART, YRBUTTONSTART, InputManager::BUTTON_R, rmessage);
        topelements.push_back(rbutton);
    }
    
    //Draw bottom button area
    const int BUTTONDISTANCE = 25;
    Button* centerbutton;
    Button* leftbutton;
    Button* rightbutton;
    //Center
    const std::string CENTERBUTTONPATH = ExtDataManager::getBasePath() + "/textures/orangebutton.png";
    const int XCENTERBUTTONSTART = (Graphic::TOPSCREENWIDTH/2) - (TextureManager::getTexture(CENTERBUTTONPATH)->width/2);
    if( State::getMode() == State::SELECTMODE || State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLESELECTMODE || State::getMode() == State::MULTIPLECLONEMODE || State::getMode() == State::EDITABLEOVERLAYMODE ) {
        if( State::getMode() == State::SELECTMODE ) {
            const int YCENTERBUTTONSTART = Graphic::TOPSCREENHEIGHT - TextureManager::getTexture(CENTERBUTTONPATH)->height;
            centerbutton = new Button(TextureManager::getTexture(CENTERBUTTONPATH), XCENTERBUTTONSTART, YCENTERBUTTONSTART, InputManager::BUTTON_A, ExtDataManager::getGuiText(ExtDataManager::EDITSTRING));
            topelements.push_back(centerbutton);
        }

        //Left
        const std::string LEFTBUTTONPATH = ExtDataManager::getBasePath() + "/textures/bluebutton.png";
        const int XLEFTBUTTONSTART = XCENTERBUTTONSTART - TextureManager::getTexture(LEFTBUTTONPATH)->width - BUTTONDISTANCE;
        const int YLEFTBUTTONSTART = Graphic::TOPSCREENHEIGHT - TextureManager::getTexture(LEFTBUTTONPATH)->height;

        std::string leftmsg;
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::MULTIPLESELECTMODE ) leftmsg = ExtDataManager::getGuiText(ExtDataManager::IMPORTSTRING);
        else if ( State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLECLONEMODE || State::getMode() == State::EDITABLEOVERLAYMODE ) leftmsg = ExtDataManager::getGuiText(ExtDataManager::CANCELSTRING);

        int lefticon;
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::MULTIPLESELECTMODE ) lefticon = InputManager::BUTTON_Y;
        else if ( State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLECLONEMODE || State::getMode() == State::EDITABLEOVERLAYMODE ) lefticon = InputManager::BUTTON_B;

        leftbutton = new Button(TextureManager::getTexture(LEFTBUTTONPATH), XLEFTBUTTONSTART, YLEFTBUTTONSTART, lefticon, leftmsg);
        topelements.push_back(leftbutton);

        //Right
        const std::string RIGHTBUTTONPATH = ExtDataManager::getBasePath() + "/textures/greenbutton.png";
        const int XRIGHTBUTTONSTART = XCENTERBUTTONSTART + TextureManager::getTexture(LEFTBUTTONPATH)->width + BUTTONDISTANCE;
        const int YRIGHTBUTTONSTART = Graphic::TOPSCREENHEIGHT - TextureManager::getTexture(RIGHTBUTTONPATH)->height;

        std::string rightmsg;
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::MULTIPLESELECTMODE ) rightmsg = ExtDataManager::getGuiText(ExtDataManager::CLONESTRING);
        else if ( State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLECLONEMODE || State::getMode() == State::EDITABLEOVERLAYMODE ) rightmsg = ExtDataManager::getGuiText(ExtDataManager::CHOOSESTRING);

        int righticon;
        if( State::getMode() == State::SELECTMODE || State::getMode() == State::MULTIPLESELECTMODE) righticon = InputManager::BUTTON_X;
        else if ( State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLECLONEMODE || State::getMode() == State::EDITABLEOVERLAYMODE ) righticon = InputManager::BUTTON_A;

        rightbutton = new Button(TextureManager::getTexture(RIGHTBUTTONPATH), XRIGHTBUTTONSTART, YRIGHTBUTTONSTART, righticon, rightmsg);
        topelements.push_back(rightbutton);
    }
    
    //Draw center screen message
    std::string centerscreenmsg;
    if( State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLECLONEMODE ) centerscreenmsg = ExtDataManager::getGuiText(ExtDataManager::SELECTCLONINGSTRING);
    if( State::getMode() == State::MULTIPLESELECTMODE ) centerscreenmsg = ExtDataManager::getGuiText(ExtDataManager::MULTIPLESELECTSTRING);
    
    if( State::getMode() == State::EDITABLEOVERLAYMODE ) {
        std::string kbreturned = State::keyboard.HBKB_CheckKeyboardInput();
        
        if( kbreturned.size() > 12) 
            kbreturned = "..." + kbreturned.substr(kbreturned.size()-12, 12);
        
        centerscreenmsg = ExtDataManager::getGuiText(ExtDataManager::SEARCHSTRING) + " " + kbreturned; 
    }
    
    Text* centerscreentxt;
    const int XCENTERSCREENMSGSTART = (Graphic::TOPSCREENWIDTH/2) - (getTextWidth(FontManager::getFont(ROBOTOBOLDPATH), 9, centerscreenmsg)/2);
    const int YCENTERSCREENMSGSTART = Graphic::TOPSCREENHEIGHT - 15;
    if( State::getMode() == State::CLONEMODE || State::getMode() == State::MULTIPLESELECTMODE || State::getMode() == State::MULTIPLECLONEMODE || State::getMode() == State::EDITABLEOVERLAYMODE ){ 
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

void drawBottomScreen() {
    std::vector<Drawable*> bottomelements;
    State::setTouchId(0);
    State::setKeyboardState(4);
    const std::string ROBOTOBOLDPATH = ExtDataManager::getBasePath() + "/fonts/roboto_bold.ttf";
    
    if( State::getMode() != State::EDITABLEOVERLAYMODE ) {
        Graphic::startFrame(Graphic::BOTTOMSCREEN);
        
        bool active = false;
        if( State::getMode() == State::EDITMODE ) active = true;
        
        Pokemon pika(State::getBoxNumber(), State::getIndexNumber(), ExtDataManager::getSave());
        
        //Draw background
        const std::string BACKGROUNDPATH = ExtDataManager::getBasePath() + "/textures/bottombackground.png";
        Drawable* background = new Drawable(TextureManager::getTexture(BACKGROUNDPATH), 0, 0);
        bottomelements.push_back(background);
        
        if( State::getTab() == State::GENERALTAB && pika.getPokedexNumber() > 0 ) {
            //Draw species info
            const std::string SPECIESINFOPATH = ExtDataManager::getBasePath() + "/textures/speciesinfo.png";
            const int XSPECIESINFOSTART = 0;
            const int YSPECIESINFOSTART = 10;
            const std::string specieswrite = ExtDataManager::getSpeciesName(pika.getPokedexNumber());

            Field* speciesfield = new Field(TextureManager::getTexture(SPECIESINFOPATH), XSPECIESINFOSTART, YSPECIESINFOSTART, active, State::SPECIESBUTTON, ExtDataManager::getGuiText(ExtDataManager::SPECIESSTRING), specieswrite, Field::POKEBALLMODE);
            bottomelements.push_back(speciesfield);

            //Draw gender sign
            Drawable* gendersign;
            if( !pika.isGenderless() ) {
                const int XGENDERPOS = XSPECIESINFOSTART + 150;
                const int YGENDERPOS = YSPECIESINFOSTART + 4;
                const std::string MALEPATH = ExtDataManager::getBasePath() + "/textures/male.png";
                const std::string FEMALEPATH = ExtDataManager::getBasePath() + "/textures/female.png";

                std::string genderpath;
                if( pika.isFemale() ) genderpath = FEMALEPATH;
                else genderpath = MALEPATH;

                gendersign = new Drawable(TextureManager::getTexture(genderpath), XGENDERPOS, YGENDERPOS, active, State::GENDERBUTTON);
                bottomelements.push_back(gendersign);
            }

            //Draw fields
            const std::string LIGHTTEXTURE = ExtDataManager::getBasePath() + "/textures/lightfield.png";
            const std::string DARKTEXTURE = ExtDataManager::getBasePath() + "/textures/darkfield.png";
            const int FIELDDISTANCE = TextureManager::getTexture(LIGHTTEXTURE)->height + 1;
            const int POSY = 17;

            //Level
            Field* levelfield = new Field(TextureManager::getTexture(LIGHTTEXTURE), 0, POSY + FIELDDISTANCE, active, State::LVBUTTONDOWN, ExtDataManager::getGuiText(ExtDataManager::LVSTRING), intTOstring(pika.getLevel(), 10), Field::ARROWMODE);
            bottomelements.push_back(levelfield);

            //Nature
            Field* naturefield = new Field(TextureManager::getTexture(DARKTEXTURE), 0, POSY + FIELDDISTANCE*2, active, State::NATUREBUTTON, ExtDataManager::getGuiText(ExtDataManager::NATURESTRING), ExtDataManager::getNatureName(pika.getNature()), Field::POKEBALLMODE);
            bottomelements.push_back(naturefield);

            //Ability
            Field* abilityfield = new Field(TextureManager::getTexture(LIGHTTEXTURE), 0, POSY + FIELDDISTANCE*3, active, State::ABILITYBUTTON, ExtDataManager::getGuiText(ExtDataManager::ABILITYSTRING), ExtDataManager::getAbilityName(pika.getAbility()), Field::POKEBALLMODE);
            bottomelements.push_back(abilityfield);

            //Item
            Field* itemfield = new Field(TextureManager::getTexture(DARKTEXTURE), 0, POSY + FIELDDISTANCE*4, active, State::ITEMBUTTON, ExtDataManager::getGuiText(ExtDataManager::ITEMSTRING), ExtDataManager::getItemName(pika.getItem()), Field::POKEBALLMODE);
            bottomelements.push_back(itemfield);

            //Ball
            Field* ballfield = new Field(TextureManager::getTexture(LIGHTTEXTURE), 0, POSY + FIELDDISTANCE*5, active, State::BALLBUTTON, ExtDataManager::getGuiText(ExtDataManager::BALLSTRING), ExtDataManager::getBallName(pika.getBall()), Field::POKEBALLMODE);
            bottomelements.push_back(ballfield);

            //Shiny
            std::string shinystring;
            if( pika.isShiny() ) shinystring = ExtDataManager::getGuiText(ExtDataManager::YESSTRING);
            else shinystring = ExtDataManager::getGuiText(ExtDataManager::NOSTRING);
             Field* shinyfield = new Field(TextureManager::getTexture(DARKTEXTURE), 0, POSY + FIELDDISTANCE*6, active, State::SHINYBUTTON, ExtDataManager::getGuiText(ExtDataManager::SHINYSTRING), shinystring, Field::POKEBALLMODE);
            bottomelements.push_back(shinyfield);

            //OT
            //Field* otfield = new Field(TextureManager::getTexture(LIGHTTEXTURE), 0, POSY + FIELDDISTANCE*7, false, State::OTBUTTON, L"OT:", pika.getOT(), Field::POKEBALLMODE);
            //bottomelements.push_back(otfield);
        }
        
        if( State::getTab() == State::COMBATTAB && pika.getPokedexNumber() > 0 ) {
            //Draw move area
            const std::string MOVETOPPATH = ExtDataManager::getBasePath() + "/textures/moveareatop.png";
            const std::string MOVELIGHTPATH = ExtDataManager::getBasePath() + "/textures/movearealight.png";
            const std::string MOVEDARKPATH = ExtDataManager::getBasePath() + "/textures/moveareadark.png";
            const int XMOVEAREAPOS = Graphic::BOTTOMSCREENWIDTH - TextureManager::getTexture(MOVETOPPATH)->width - 5;
            const int YMOVEAREAPOS = 10;
            const int MOVEAREADISTANCE = TextureManager::getTexture(MOVETOPPATH)->height + 1;
            
            //Move top
            Drawable* movetop = new Drawable(TextureManager::getTexture(MOVETOPPATH), XMOVEAREAPOS, YMOVEAREAPOS);
            bottomelements.push_back(movetop);
            
            Text* movetext = new Text(FontManager::getFont(ROBOTOBOLDPATH), XMOVEAREAPOS+5, YMOVEAREAPOS+3, 9, Text::WHITE, ExtDataManager::getGuiText(ExtDataManager::MOVESSTRING));
            bottomelements.push_back(movetext);
            
            //Move1
            Field* move1field = new Field(TextureManager::getTexture(MOVELIGHTPATH), XMOVEAREAPOS, YMOVEAREAPOS + MOVEAREADISTANCE, active, State::MOVE1BUTTON, ExtDataManager::getMoveName(pika.getMove(0)), "", Field::POKEBALLMODE);
            bottomelements.push_back(move1field);
            
            //Move2
            Field* move2field = new Field(TextureManager::getTexture(MOVEDARKPATH), XMOVEAREAPOS, YMOVEAREAPOS + MOVEAREADISTANCE*2, active, State::MOVE2BUTTON, ExtDataManager::getMoveName(pika.getMove(1)), "", Field::POKEBALLMODE);
            bottomelements.push_back(move2field);
            
            //Move3
            Field* move3field = new Field(TextureManager::getTexture(MOVELIGHTPATH), XMOVEAREAPOS, YMOVEAREAPOS + MOVEAREADISTANCE*3, active, State::MOVE3BUTTON, ExtDataManager::getMoveName(pika.getMove(2)), "", Field::POKEBALLMODE);
            bottomelements.push_back(move3field);
            
            //Move4
            Field* move4field = new Field(TextureManager::getTexture(MOVEDARKPATH), XMOVEAREAPOS, YMOVEAREAPOS + MOVEAREADISTANCE*4, active, State::MOVE4BUTTON, ExtDataManager::getMoveName(pika.getMove(3)), "", Field::POKEBALLMODE);
            bottomelements.push_back(move4field);
            
            //EggMove top
            Drawable* eggmovetop = new Drawable(TextureManager::getTexture(MOVETOPPATH), XMOVEAREAPOS, YMOVEAREAPOS + MOVEAREADISTANCE*5 + 5);
            bottomelements.push_back(eggmovetop);
            
            Text* eggmovetext = new Text(FontManager::getFont(ROBOTOBOLDPATH), XMOVEAREAPOS+5, YMOVEAREAPOS + MOVEAREADISTANCE*5 +5+3, 9, Text::WHITE, ExtDataManager::getGuiText(ExtDataManager::EGGMOVESSTRING));
            bottomelements.push_back(eggmovetext);
            
            //EggMove1
            Field* eggmove1field = new Field(TextureManager::getTexture(MOVELIGHTPATH), XMOVEAREAPOS, YMOVEAREAPOS + MOVEAREADISTANCE*6 + 5, active, State::EGGMOVE1BUTTON, ExtDataManager::getMoveName(pika.getEggmove(0)), "", Field::POKEBALLMODE);
            bottomelements.push_back(eggmove1field);
            
            //EggMove2
            Field* eggmove2field = new Field(TextureManager::getTexture(MOVEDARKPATH), XMOVEAREAPOS, YMOVEAREAPOS + MOVEAREADISTANCE*7 + 5, active, State::EGGMOVE2BUTTON, ExtDataManager::getMoveName(pika.getEggmove(1)), "", Field::POKEBALLMODE);
            bottomelements.push_back(eggmove2field);
            
            //EggMove3
            Field* eggmove3field = new Field(TextureManager::getTexture(MOVELIGHTPATH), XMOVEAREAPOS, YMOVEAREAPOS + MOVEAREADISTANCE*8 + 5, active, State::EGGMOVE3BUTTON, ExtDataManager::getMoveName(pika.getEggmove(2)), "", Field::POKEBALLMODE);
            bottomelements.push_back(eggmove3field);
            
            //EggMove4
            Field* eggmove4field = new Field(TextureManager::getTexture(MOVEDARKPATH), XMOVEAREAPOS, YMOVEAREAPOS + MOVEAREADISTANCE*9 + 5, active, State::EGGMOVE4BUTTON, ExtDataManager::getMoveName(pika.getEggmove(3)), "", Field::POKEBALLMODE);
            bottomelements.push_back(eggmove4field);
            
            //Draw stats area
            const std::string STATSTOPPATH = ExtDataManager::getBasePath() + "/textures/statsareatop.png";
            const std::string STATSLIGHTPATH = ExtDataManager::getBasePath() + "/textures/statsarealight.png";
            const std::string STATSDARKPATH = ExtDataManager::getBasePath() + "/textures/statsareadark.png";
            const int XSTATSAREAPOS = 0;
            const int YSTATSAREAPOS = 10;
            const int STATSAREADISTANCE = TextureManager::getTexture(STATSTOPPATH)->height + 1;
            
            //Stats top
            Drawable* statstop = new Drawable(TextureManager::getTexture(STATSTOPPATH), XSTATSAREAPOS, YSTATSAREAPOS);
            bottomelements.push_back(statstop);
            
            Text* statstext = new Text(FontManager::getFont(ROBOTOBOLDPATH), XSTATSAREAPOS+5, YSTATSAREAPOS+3, 9, Text::WHITE, ExtDataManager::getGuiText(ExtDataManager::STATSSTRING));
            bottomelements.push_back(statstext);
            
            //Draw iv
            const int XIVPOS = 40;
            const int XIVEDITPOS = 45;
            const int XEVPOS = 75;
            const int XEVEDITPOS = 100;
            const int XTOTALPOS = 110;
            
            int ivpos = XIVPOS;
            if(active) ivpos = XIVEDITPOS;
            int evpos = XEVPOS;
            if(active) evpos = XEVEDITPOS;
            
            Text* ivtext = new Text(FontManager::getFont(ROBOTOBOLDPATH), ivpos, YSTATSAREAPOS + STATSAREADISTANCE + 5, 9, Text::WHITE, ExtDataManager::getGuiText(ExtDataManager::IVSTRING));
            bottomelements.push_back(ivtext);
            
            Text* evtext = new Text(FontManager::getFont(ROBOTOBOLDPATH), evpos, YSTATSAREAPOS + STATSAREADISTANCE + 5, 9, Text::WHITE, ExtDataManager::getGuiText(ExtDataManager::EVSTRING));
            bottomelements.push_back(evtext);
            
            if(!active) {
                Text* totaltext = new Text(FontManager::getFont(ROBOTOBOLDPATH), XTOTALPOS, YSTATSAREAPOS + STATSAREADISTANCE + 5, 9, Text::WHITE, ExtDataManager::getGuiText(ExtDataManager::TOTALSTRING));
                bottomelements.push_back(totaltext);
            }
            
            //Stats Hp
            MultiField* hpfield = new MultiField(TextureManager::getTexture(STATSLIGHTPATH), XSTATSAREAPOS, YSTATSAREAPOS  + STATSAREADISTANCE*2, active, State::HPIVBUTTONDOWN, State::HPEVBUTTONDOWN, ExtDataManager::getGuiText(ExtDataManager::HPSTRING), intTOstring(pika.getIV(Pokemon::HP), 10), intTOstring(pika.getEV(Pokemon::HP), 10), intTOstring(pika.getStat(Pokemon::HP), 10));
            bottomelements.push_back(hpfield);
            
            //Stats atk
            MultiField* atkfield = new MultiField(TextureManager::getTexture(STATSDARKPATH), XSTATSAREAPOS, YSTATSAREAPOS  + STATSAREADISTANCE*3, active, State::ATKIVBUTTONDOWN, State::ATKEVBUTTONDOWN, ExtDataManager::getGuiText(ExtDataManager::ATKSTRING), intTOstring(pika.getIV(Pokemon::ATK), 10), intTOstring(pika.getEV(Pokemon::ATK), 10), intTOstring(pika.getStat(Pokemon::ATK), 10));
            bottomelements.push_back(atkfield);
            
            //Stats def
            MultiField* deffield = new MultiField(TextureManager::getTexture(STATSLIGHTPATH), XSTATSAREAPOS, YSTATSAREAPOS  + STATSAREADISTANCE*4, active, State::DEFIVBUTTONDOWN, State::DEFEVBUTTONDOWN, ExtDataManager::getGuiText(ExtDataManager::DEFSTRING), intTOstring(pika.getIV(Pokemon::DEF), 10), intTOstring(pika.getEV(Pokemon::DEF), 10), intTOstring(pika.getStat(Pokemon::DEF), 10));
            bottomelements.push_back(deffield);
            
            //Stats spa
            MultiField* spafield = new MultiField(TextureManager::getTexture(STATSDARKPATH), XSTATSAREAPOS, YSTATSAREAPOS  + STATSAREADISTANCE*5, active, State::SPAIVBUTTONDOWN, State::SPAEVBUTTONDOWN, ExtDataManager::getGuiText(ExtDataManager::SPASTRING), intTOstring(pika.getIV(Pokemon::SPA), 10), intTOstring(pika.getEV(Pokemon::SPA), 10), intTOstring(pika.getStat(Pokemon::SPA), 10));
            bottomelements.push_back(spafield);
            
            //Stats spd
            MultiField* spdfield = new MultiField(TextureManager::getTexture(STATSLIGHTPATH), XSTATSAREAPOS, YSTATSAREAPOS  + STATSAREADISTANCE*6, active, State::SPDIVBUTTONDOWN, State::SPDEVBUTTONDOWN, ExtDataManager::getGuiText(ExtDataManager::SPDSTRING), intTOstring(pika.getIV(Pokemon::SPD), 10), intTOstring(pika.getEV(Pokemon::SPD), 10), intTOstring(pika.getStat(Pokemon::SPD), 10));
            bottomelements.push_back(spdfield);
            
            //Stats spe
            MultiField* spefield = new MultiField(TextureManager::getTexture(STATSDARKPATH), XSTATSAREAPOS, YSTATSAREAPOS  + STATSAREADISTANCE*7, active, State::SPEIVBUTTONDOWN, State::SPEEVBUTTONDOWN, ExtDataManager::getGuiText(ExtDataManager::SPESTRING), intTOstring(pika.getIV(Pokemon::SPE), 10), intTOstring(pika.getEV(Pokemon::SPE), 10), intTOstring(pika.getStat(Pokemon::SPE), 10));
            bottomelements.push_back(spefield);
        }
        
        //Draw buttons
        const std::string LIGHTPATH = ExtDataManager::getBasePath() + "/textures/lightbottombutton.png";
        const std::string DARKPATH = ExtDataManager::getBasePath() + "/textures/darkbottombutton.png";
        const int XPOS = 0;
        const int YEXPORTPOS = Graphic::BOTTOMSCREENHEIGHT - (TextureManager::getTexture(DARKPATH)->height*3);
        const int YSAVEPOS = Graphic::BOTTOMSCREENHEIGHT - (TextureManager::getTexture(DARKPATH)->height*2);
        const int YCANCELPOS = Graphic::BOTTOMSCREENHEIGHT - TextureManager::getTexture(DARKPATH)->height;
        LargeButton* cancelbutton;
        LargeButton* savebutton;
        LargeButton* exportbutton;
        
        if( State::getMode() == State::EDITMODE ) {
            cancelbutton = new LargeButton(TextureManager::getTexture(DARKPATH), XPOS, YCANCELPOS, InputManager::BUTTON_B, ExtDataManager::getGuiText(ExtDataManager::CANCELSTRING));
            bottomelements.push_back(cancelbutton);
            
            savebutton = new LargeButton(TextureManager::getTexture(LIGHTPATH), XPOS, YSAVEPOS, InputManager::BUTTON_A, ExtDataManager::getGuiText(ExtDataManager::SAVESTRING));
            bottomelements.push_back(savebutton);
            
            exportbutton = new LargeButton(TextureManager::getTexture(DARKPATH), XPOS, YEXPORTPOS, InputManager::BUTTON_Y, ExtDataManager::getGuiText(ExtDataManager::EXPORTSTRING));
            bottomelements.push_back(exportbutton);
        }
        
        //Draw change tab
        const std::string TABPATH = ExtDataManager::getBasePath() + "/textures/tab.png";
        const int XTABPOS = Graphic::BOTTOMSCREENWIDTH - (TextureManager::getTexture(TABPATH)->width) - 5;
        const int YTABPOS = Graphic::BOTTOMSCREENHEIGHT - (TextureManager::getTexture(TABPATH)->height);
        
        Drawable* tab = new Drawable(TextureManager::getTexture(TABPATH), XTABPOS, YTABPOS, true, State::TABBUTTON);
        bottomelements.push_back(tab);
        
        std::string tabstring;
        if( State::getTab() == State::GENERALTAB ) tabstring = ExtDataManager::getGuiText(ExtDataManager::COMBATTABSTRING);
        if( State::getTab() == State::COMBATTAB ) tabstring = ExtDataManager::getGuiText(ExtDataManager::GENERALTABSTRING);
        
        Text* tabtext = new Text(FontManager::getFont(ROBOTOBOLDPATH), XTABPOS+5, YTABPOS+3, 9, Text::WHITE, tabstring);
        bottomelements.push_back(tabtext);
        
        for(unsigned int i = 0; i < bottomelements.size(); i++)
            bottomelements[i]->draw();
        
        for( unsigned int i = 0; i < bottomelements.size(); i++ ) {
            int returned = bottomelements[i]->isTouched(InputManager::scanTouch());
            if( returned )
                State::setTouchId(returned);
        }
                
        for(unsigned int i = 0; i < bottomelements.size(); i++)
            delete bottomelements[i];
        
        Graphic::endFrame();
    }
    
    else
        callKeyboard();
}

void callKeyboard() {
    const int KEYBOARDDELAY = 40;
    
    if(State::getMode() == State::EDITABLEOVERLAYMODE && State::getKeyboardDelay() > KEYBOARDDELAY) 
        State::setKeyboardState(State::keyboard.HBKB_CallKeyboard(InputManager::scanTouch()));
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
    std::vector<std::string> result = FileSystem::obtainFileList("/pk/PCHex++/import", "pk6");
    
    if( result.empty() ) {
        State::setOverlayMsg(ExtDataManager::getGuiText(ExtDataManager::NOCONTENTSTRING));
        State::setBackupMode(State::SELECTMODE);
        State::setMode(State::OVERLAYMODE);
    }
    
    else {
        State::setEovMode(State::IMPORTEOV);
        State::setOverlayMsg(ExtDataManager::getGuiText(ExtDataManager::SELECTPK6STRING));
        State::setEovVector(result);
        State::setBackupMode(State::SELECTMODE);
        State::setMode(State::EDITABLEOVERLAYMODE);
    }
}

void import() {
    std::string importpath;
    
    importpath = "/pk/PCHex++/import/" + State::getCurrentFolder() + "/" + State::getEovVector()[State::getEovSelected()];
        
    if( FileSystem::isDirectory(importpath) ) {
        State::setCurrentFolder(State::getCurrentFolder()+"/"+State::getEovVector()[State::getEovSelected()]);
        State::getEovVector().clear();
            
        std::vector<std::string> result = FileSystem::obtainFileList(importpath, "pk6");
        
        if( result.empty() ) {
            State::setOverlayMsg(ExtDataManager::getGuiText(ExtDataManager::NOCONTENTSTRING));
            State::setBackupMode(State::SELECTMODE);
            State::setMode(State::OVERLAYMODE);
            State::setEovSelected(0);
            State::setCurrentFolder("");
            State::setSkip(0);
            State::keyboard.HBKB_Clean();
        }
    
        else {
            State::setEovMode(State::IMPORTEOV);
            State::setOverlayMsg(ExtDataManager::getGuiText(ExtDataManager::SELECTPK6STRING));
            State::setEovVector(result);
            State::setBackupMode(State::SELECTMODE);
            State::setMode(State::EDITABLEOVERLAYMODE);
            State::setEovSelected(0);
            State::setSkip(0);
        }
    }
    
    else {
        Pokemon toimport(State::getBoxNumber(), State::getIndexNumber(), ExtDataManager::getSave());

        std::string overlaymsg;
        if( toimport.importPK6(importpath) != 0 ) overlaymsg = ExtDataManager::getGuiText(ExtDataManager::FAILEDSTRING);
        else overlaymsg = ExtDataManager::getGuiText(ExtDataManager::SUCCESSSSTRING);
        State::setOverlayMsg(overlaymsg);
        State::setMode(State::OVERLAYMODE);
        State::setEovSelected(0);
        State::setCurrentFolder("");
        State::setSkip(0);
        State::getEovVector().clear();
        State::keyboard.HBKB_Clean();
    }
}

void closeEov() {
    State::setEovSelected(0);
    State::setSkip(0);
    State::getEovVector().clear();
    State::keyboard.HBKB_Clean();
    State::setMode(State::getBackupMode());
}

void search() {
    std::string tosearch = State::keyboard.HBKB_CheckKeyboardInput();
    std::transform(tosearch.begin(), tosearch.end(), tosearch.begin(), ::tolower);
    
    std::vector<std::string> bufferelement = State::getEovVector();
    for(unsigned int i = 0; i < bufferelement.size(); i++)
        std::transform(bufferelement[i].begin(), bufferelement[i].end(), bufferelement[i].begin(), ::tolower);
    
    unsigned int temp = 0;
    unsigned int i = 0;
    bool found;
    int skipcount = -1;
    do {
        found = false;
        for(i = temp; i < bufferelement.size() && !found; i++) 
            if(tosearch == bufferelement[i].substr(0, tosearch.size())) 
               found = true;
        
        skipcount++;
        temp = i;
    }while(skipcount < State::getSkip());
        
    if(found) State::setEovSelected(i-1);
    else State::setSkip(State::getSkip()-1);
}

void selectNature() {
    State::setOverlayMsg(ExtDataManager::getGuiText(ExtDataManager::SELECTNATURESTRING));
    State::setEovMode(State::NATUREEOV);
    State::setEovVector(ExtDataManager::getNaturesNameVector());
    State::setBackupMode(State::EDITMODE);
    State::setMode(State::EDITABLEOVERLAYMODE);
}

void editNature() {
    Pokemon pika(State::getBoxNumber(), State::getIndexNumber(), ExtDataManager::getSave());
    pika.setNature(State::getEovSelected());
    closeEov();
}

void commitSave() {
    std::string msg;
    if( ExtDataManager::getSave()->writeSaveFile() != 0 ) msg = ExtDataManager::getGuiText(ExtDataManager::FAILEDSTRING);
    else msg = ExtDataManager::getGuiText(ExtDataManager::SUCCESSSSTRING);
    
    State::setOverlayMsg(msg);
    State::setBackupMode(State::SELECTMODE);
    State::setMode(State::OVERLAYMODE);
}

void exprt() {
    std::string msg;
    Pokemon pika(State::getBoxNumber(), State::getIndexNumber(), ExtDataManager::getSave());
    if( pika.exportPK6("/pk/PCHex++/export/"+ExtDataManager::getSpeciesName(pika.getPokedexNumber())+"_"+intTOstring(pika.getPID(), 10)) != 0 ) msg = ExtDataManager::getGuiText(ExtDataManager::FAILEDSTRING);
    else msg = ExtDataManager::getGuiText(ExtDataManager::SUCCESSSSTRING);
    
    State::setOverlayMsg(msg);
    State::setBackupMode(State::EDITMODE);
    State::setMode(State::OVERLAYMODE);
}

void selectAbility() {
    State::setOverlayMsg(ExtDataManager::getGuiText(ExtDataManager::SELECTABILITYSTRING));
    State::setEovMode(State::ABILITYEOV);
    State::setEovVector(ExtDataManager::getAbilitiesNameVector());
    State::setBackupMode(State::EDITMODE);
    State::setMode(State::EDITABLEOVERLAYMODE);
}

void editAbility() {
    Pokemon pika(State::getBoxNumber(), State::getIndexNumber(), ExtDataManager::getSave());
    pika.setAbility(State::getEovSelected());
    closeEov();
}

void selectItem() {
    State::setOverlayMsg(ExtDataManager::getGuiText(ExtDataManager::SELECTITEMSTRING));
    State::setEovMode(State::ITEMEOV);
    State::setEovVector(ExtDataManager::getItemsNameVector());
    State::setBackupMode(State::EDITMODE);
    State::setMode(State::EDITABLEOVERLAYMODE);
}

void editItem() {
    Pokemon pika(State::getBoxNumber(), State::getIndexNumber(), ExtDataManager::getSave());
    pika.setItem(State::getEovSelected());
    closeEov();
}

void selectBall() {
    State::setOverlayMsg(ExtDataManager::getGuiText(ExtDataManager::SELECTBALLSTRING));
    State::setEovMode(State::BALLEOV);
    State::setEovVector(ExtDataManager::getBallsNameVector());
    State::setBackupMode(State::EDITMODE);
    State::setMode(State::EDITABLEOVERLAYMODE);
}

void editBall() {
    Pokemon pika(State::getBoxNumber(), State::getIndexNumber(), ExtDataManager::getSave());
    pika.setBall(State::getEovSelected());
    closeEov();
}

void setShiny() {
    Pokemon pika(State::getBoxNumber(), State::getIndexNumber(), ExtDataManager::getSave());
    pika.setShiny(!pika.isShiny());
}

void setGender() {
    Pokemon pika(State::getBoxNumber(), State::getIndexNumber(), ExtDataManager::getSave());
    pika.setGender(!pika.isFemale());
}

void selectSpecies() {
    State::setOverlayMsg(ExtDataManager::getGuiText(ExtDataManager::SELECTSPECIESSTRING));
    State::setEovMode(State::SPECIESEOV);
    State::setEovVector(ExtDataManager::getSpeciesNameVector());
    State::setBackupMode(State::EDITMODE);
    State::setMode(State::EDITABLEOVERLAYMODE);
}

void editSpecies() {
    Pokemon pika(State::getBoxNumber(), State::getIndexNumber(), ExtDataManager::getSave());
    pika.setPokedexNumber(State::getEovSelected());
    Pokemon pika2(State::getBoxNumber(), State::getIndexNumber(), ExtDataManager::getSave());
    if( !pika2.isNicknamed() )
        pika2.setNickname(ExtDataManager::getSpeciesName(State::getEovSelected()));
    
    closeEov();
}

void startEdit() {
    Pokemon pika(State::getBoxNumber(), State::getIndexNumber(), ExtDataManager::getSave());
    State::setTempBackup(&pika);
    State::setMode(State::EDITMODE);
}

void cancelEdit() {
    Pokemon pika(State::getBoxNumber(), State::getIndexNumber(), ExtDataManager::getSave());
    State::getTempBackup(&pika);
    State::setMode(State::SELECTMODE);
}

void selectMove(const int val) {
    State::setOverlayMsg(ExtDataManager::getGuiText(ExtDataManager::SELECTMOVESTRING));
    State::setEovMode(val);
    State::setEovVector(ExtDataManager::getMovesNameVector());
    State::setBackupMode(State::EDITMODE);
    State::setMode(State::EDITABLEOVERLAYMODE);
}

void editMove() {
    Pokemon pika(State::getBoxNumber(), State::getIndexNumber(), ExtDataManager::getSave());
    int val = State::getEovMode() - State::MOVE1BUTTON;
    pika.setMove(State::getEovSelected(), val);
    closeEov();
}

void editEggMove() {
    Pokemon pika(State::getBoxNumber(), State::getIndexNumber(), ExtDataManager::getSave());
    int val = State::getEovMode() - State::EGGMOVE1BUTTON;
    pika.setEggmove(State::getEovSelected(), val);
    closeEov();
}