#include <vector>

#include "button.h"
#include "inputmanager.h"
#include "extdatamanager.h"
#include "texturemanager.h"
#include "fontmanager.h"
#include "utility.h"

Button::Button(raw_texture* texture, const int posx, const int posy, const int button, const std::string msg) : Drawable(texture, posx, posy) {
    this->button = button;
    this->msg = msg;
}

void Button::draw() {
    std::vector<Drawable*> elements;
    
    //Draw texture
    Drawable* maintexture = new Drawable(texture, posx, posy);
    elements.push_back(maintexture);
    
    //Draw button
    std::string buttontype;
    if(button == InputManager::BUTTON_A) buttontype = "a";
    if(button == InputManager::BUTTON_B) buttontype = "b";
    if(button == InputManager::BUTTON_X) buttontype = "x";
    if(button == InputManager::BUTTON_Y) buttontype = "y";
    if(button == InputManager::BUTTON_L) buttontype = "l";
    if(button == InputManager::BUTTON_R) buttontype = "r";
    
    const int BUTTONDISTANCE = 10;
    
    const std::string BUTTONPATH = ExtDataManager::getBasePath() + "/textures/" + buttontype + "button.png";
    const int XBUTTONSTART = posx +  BUTTONDISTANCE;
    const int YBUTTONSTART = posy + 6;
    Drawable* buttontexture = new Drawable(TextureManager::getTexture(BUTTONPATH), XBUTTONSTART, YBUTTONSTART);
    elements.push_back(buttontexture);
    
    //Draw Text
    const std::string FONTPATH = ExtDataManager::getBasePath() + "/fonts/roboto_bold.ttf";
    const int HALFDISTANCE = ((texture->width - (BUTTONDISTANCE + TextureManager::getTexture(BUTTONPATH)->width))/2);
    const int XTEXTSTART = posx + BUTTONDISTANCE + TextureManager::getTexture(BUTTONPATH)->width + HALFDISTANCE - (getTextWidth(FontManager::getFont(FONTPATH), 9, msg)/2) - 3;
    const int YTEXTSTART = posy + 8;
    Text* info = new Text(FontManager::getFont(FONTPATH), XTEXTSTART, YTEXTSTART, 9, Text::WHITE, msg);
    elements.push_back(info);
    
    
    for(unsigned int i = 0; i < elements.size(); i++)
        elements[i]->draw();
    
    for(unsigned int i = 0; i < elements.size(); i++)
        delete elements[i];
}