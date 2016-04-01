#include <vector>

#include "field.h"
#include "extdatamanager.h"
#include "fontmanager.h"
#include "text.h"
#include "utility.h"

Field::Field(raw_texture* texture, const int posx, const int posy, const bool active, const int id, const std::string label, const std::string textfield, const int mode) : Drawable(texture, posx, posy, active, id) {
    this->label = label;
    this->textfield = textfield;
    this->mode = mode;
    this->istextfieldwide = false;
}

Field::Field(raw_texture* texture, const int posx, const int posy, const bool active, const int id, const std::wstring label, const std::wstring textfield, const int mode) : Drawable(texture, posx, posy, active, id) {
    this->labelwide = label;
    this->textfieldwide = textfield;
    this->mode = mode;
    this->istextfieldwide = true;
}

void Field::draw() {
    std::vector<Drawable*> elements;
    const std::string FONTPATH = ExtDataManager::getBasePath() + "/fonts/roboto_bold.ttf";
    
    if( mode == POKEBALLMODE ) {
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
        
        Text* labeltext;
        if( istextfieldwide ) {
            labeltext = new Text(FontManager::getFont(FONTPATH), xlabelpos, YLABELPOS, 9, Text::WHITE, labelwide+L" "+textfieldwide);
            elements.push_back(labeltext);
        }
        
        else {
            labeltext = new Text(FontManager::getFont(FONTPATH), xlabelpos, YLABELPOS, 9, Text::WHITE, label+" "+textfield);
            elements.push_back(labeltext);
        }

        //Draw info
        /*
        const int XINFOPOS = posx + 90;
        const int YINFOPOS = YLABELPOS;

        Text* infotext = new Text(FontManager::getFont(FONTPATH), XINFOPOS, YINFOPOS, 9, Text::WHITE, textfield);
        elements.push_back(infotext);*/
    }
    
    if( mode == ARROWMODE ) {
        //Draw texture
        const std::string DOWNARROW = ExtDataManager::getBasePath() + "/textures/downarrow.png";
        const std::string UPARROW = ExtDataManager::getBasePath() + "/textures/uparrow.png";
        Drawable* tex = new Drawable(texture, posx, posy);
        elements.push_back(tex);

        //Draw label
        const int XLABELPOS = posx + 5;
        const int XLABELARROWPOS = posx + 5 + TextureManager::getTexture(DOWNARROW)->width + 5;
        const int YLABELPOS = posy + 3;
        int labelpos;
        
        if( active ) labelpos = XLABELARROWPOS;
        else labelpos = XLABELPOS;

        Text* labeltext = new Text(FontManager::getFont(FONTPATH), labelpos, YLABELPOS, 9, Text::WHITE, label+" "+textfield);
        elements.push_back(labeltext);

        /*
        //Draw info
        const int XINFOPOS = posx + 90;
        const int YINFOPOS = YLABELPOS;

        Text* infotext = new Text(FontManager::getFont(FONTPATH), XINFOPOS, YINFOPOS, 9, RGBA8(255, 255, 255, 255), );
        elements.push_back(infotext);*/

        //Draw down and up arrow
        if( active ) {
            const int XDOWNPOS = posx + 5 /*- TextureManager::getTexture(DOWNARROW)->width - 3*/;
            const int YDOWNPOS = posy + 2;
            const int XUPPOS = labelpos + getTextWidth(FontManager::getFont(FONTPATH), 9, label+" "+textfield) + 5;
            const int YUPPOS = YDOWNPOS;

            Drawable* down = new Drawable(TextureManager::getTexture(DOWNARROW), XDOWNPOS, YDOWNPOS);
            elements.push_back(down);

            Drawable* up = new Drawable(TextureManager::getTexture(UPARROW), XUPPOS, YUPPOS);
            elements.push_back(up);
        }
    }

    for(unsigned int i = 0; i < elements.size(); i++) 
        elements[i]->draw();
    
    for(unsigned int i = 0; i < elements.size(); i++) 
        delete elements[i];
}

int Field::isTouched(const touchPosition& touch) {
    if( mode == POKEBALLMODE ) {
        const std::string BALLTEXTURE = ExtDataManager::getBasePath() + "/textures/ball.png";
        const int XLABELPOS = posx + 5;
        const int XBALLPOS = XLABELPOS;
        const int YBALLPOS = posy + 2;

        Drawable ball(TextureManager::getTexture(BALLTEXTURE), XBALLPOS, YBALLPOS, active, id);
        return ball.isTouched(touch);
    }
    
    if( mode == ARROWMODE) {
        const int XDOWNPOS = posx + 5;
        const int YDOWNPOS = posy + 2;
        const std::string DOWNARROW = ExtDataManager::getBasePath() + "/textures/downarrow.png";
        
        const std::string FONTPATH = ExtDataManager::getBasePath() + "/fonts/roboto_bold.ttf";
        const int XLABELARROWPOS = posx + 5 + TextureManager::getTexture(DOWNARROW)->width + 5;
        const int XUPPOS = XLABELARROWPOS + getTextWidth(FontManager::getFont(FONTPATH), 9, label+" "+textfield) + 5;
        const int YUPPOS = YDOWNPOS;
        const std::string UPARROW = ExtDataManager::getBasePath() + "/textures/uparrow.png";
        
        Drawable downarrow(TextureManager::getTexture(DOWNARROW), XDOWNPOS, YDOWNPOS, active, id);
        Drawable uparrow(TextureManager::getTexture(UPARROW), XUPPOS, YUPPOS, active, id+1);
        
        if( downarrow.isTouched(touch) )
            return id;
        
        if( uparrow.isTouched(touch) )
            return id+1;
                    
        return 0;
    }
    
    return 0;
}