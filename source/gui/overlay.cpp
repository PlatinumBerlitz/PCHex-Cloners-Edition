#include <vector>

#include "overlay.h"
#include "graphic.h"
#include "utility.h"
#include "extdatamanager.h"

Overlay::Overlay(raw_texture* texture, const std::string msg) : Drawable(texture, (Graphic::TOPSCREENWIDTH/2) - (texture->width/2), (Graphic::TOPSCREENHEIGHT/2) - (texture->height/2)) {
    this->msg = msg;
} 

void Overlay::draw() {
    std::vector<Drawable*> elements;
    
    //Draw texture
    Drawable* maintexture = new Drawable(texture, posx, posy);
    elements.push_back(maintexture);
    
    //Draw text
    const std::string FONTPATH = ExtDataManager::getBasePath() + "/fonts/roboto_bold.ttf";
    const int YTEXTSTART = posy + 30;
    const int XTEXTSTART = posx + (texture->width/2) - (getTextWidth(FontManager::getFont(FONTPATH), 9, msg)/2);
    Text* text = new Text(FontManager::getFont(FONTPATH), XTEXTSTART, YTEXTSTART, 9, Text::WHITE, msg);
    elements.push_back(text);
    
    for(unsigned int i = 0; i < elements.size(); i++)
        elements[i]->draw();
    
    for(unsigned int i = 0; i < elements.size(); i++)
        delete elements[i];
}