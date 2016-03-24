#include <vector>

#include "field.h"
#include "extdatamanager.h"
#include "fontmanager.h"
#include "text.h"

Field::Field(raw_texture* texture, const int posx, const int posy, const bool active, const int id, const std::string label, const std::string textfield, const int mode) : Drawable(texture, posx, posy, active, id) {
    this->label = label;
    this->textfield = textfield;
    this->mode = mode;
}

void Field::draw() {
    std::vector<Drawable*> elements;
    const std::string FONTPATH = ExtDataManager::getBasePath() + "/fonts/roboto_bold.ttf";
    const std::string BALLTEXTURE = ExtDataManager::getBasePath() + "/textures/ball.png";
    
    const int XLABELPOS = posx + 5;
    const int XLABELEDITPOS = posx + TextureManager::getTexture(BALLTEXTURE)->width + 10;
    const int YLABELPOS = posy + (texture->height/2) - 3;
    
    //Draw texture
    Drawable* tex = new Drawable(texture, posx, posy);
    elements.push_back(tex);
    
    //Draw ball
    if( active ) {
        const int XBALLPOS = XLABELPOS;
        const int YBALLPOS = posy + 2;

        Drawable* ball = new Drawable(TextureManager::getTexture(BALLTEXTURE), XBALLPOS, YBALLPOS);
        elements.push_back(ball);
    }
    
    //Draw label
    int xlabelpos;
    if( !active ) xlabelpos = XLABELPOS;
    else xlabelpos = XLABELEDITPOS;

    Text* labeltext = new Text(FontManager::getFont(FONTPATH), xlabelpos, YLABELPOS, 9, Text::WHITE, label+" "+textfield);
    elements.push_back(labeltext);
               
    //Draw info
    /*
    const int XINFOPOS = posx + 90;
    const int YINFOPOS = YLABELPOS;

    Text* infotext = new Text(FontManager::getFont(FONTPATH), XINFOPOS, YINFOPOS, 9, Text::WHITE, textfield);
    elements.push_back(infotext);*/
    
    for(unsigned int i = 0; i < elements.size(); i++) 
        elements[i]->draw();
    
    for(unsigned int i = 0; i < elements.size(); i++) 
        delete elements[i];
}

int Field::isTouched(const touchPosition& touch) {
    const std::string BALLTEXTURE = ExtDataManager::getBasePath() + "/textures/ball.png";
    const int XLABELPOS = posx + 5;
    const int XBALLPOS = XLABELPOS;
    const int YBALLPOS = posy + 2;
    
    Drawable ball(TextureManager::getTexture(BALLTEXTURE), XBALLPOS, YBALLPOS, active, id);
    return ball.isTouched(touch);
    
}