#include <vector>
#include <string>

#include "box.h"
#include "boxslot.h"
#include "pokemon.h"
#include "state.h"
#include "extdatamanager.h"

Box::Box(const int posx, const int posy) : Drawable(nullptr, posx, posy) {
    
}

void Box::draw() {
    std::vector<Drawable*> elements;
    //Draw algorithm
    const int NUMBERROW = 5;
    const int NUMBERCOLUMN = 3;
    
    int j = (State::getIndexNumber()/(NUMBERROW*NUMBERCOLUMN) * (NUMBERROW*NUMBERCOLUMN));
    int k = (State::getIndexNumber()/(NUMBERROW*NUMBERCOLUMN));
    
    bool tick = State::getMultipleSelectionTick();
    for(int i = 0; i < NUMBERROW*NUMBERCOLUMN; i++) {
        const int XBOXSTART = posx;
        const int YBOXSTART = posy;
        const int YBOXDISTANCE = 5;
        const int XBOXDISTANCE = 5;
        
        std::string texturepath;
        
        if( State::getMode() == State::MULTIPLESELECTMODE || State::getMode() == State::MULTIPLECLONEMODE ) {
            if(tick)
                texturepath = ExtDataManager::getBasePath() + "/textures/boxslot_selected.png";
            
            else texturepath = ExtDataManager::getBasePath() + "/textures/boxslot.png";
        }
        
        else {
            if( State::getIndexNumber() == (i+(k*NUMBERROW*NUMBERCOLUMN)) )
                texturepath = ExtDataManager::getBasePath() + "/textures/boxslot_selected.png";

            else texturepath = ExtDataManager::getBasePath() + "/textures/boxslot.png";
        }
        
        int row = i / NUMBERCOLUMN;
        int column = i % NUMBERCOLUMN;
        const int XPOS = XBOXSTART + (XBOXDISTANCE*column) + (TextureManager::getTexture(texturepath)->width*column);
        const int YPOS = YBOXSTART + (YBOXDISTANCE*row) + (TextureManager::getTexture(texturepath)->height*row);
        
        Pokemon pika(State::getBoxNumber(), j, ExtDataManager::getSave());
        Drawable* box = new BoxSlot(TextureManager::getTexture(texturepath), XPOS, YPOS, pika);
        elements.push_back(box);
        j++;
    }
    
    for(unsigned int i = 0; i < elements.size(); i++)
        elements[i]->draw();
    
    for(unsigned int i = 0; i < elements.size(); i++)
        delete elements[i];
}

