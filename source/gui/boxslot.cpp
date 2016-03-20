#include <vector>

#include "boxslot.h"
#include "extdatamanager.h"
#include "fontmanager.h"
#include "texturemanager.h"
#include "text.h"
#include "utility.h"

BoxSlot::BoxSlot(raw_texture* tex, const int posx, const int posy, Pokemon pika) : Drawable(tex, posx, posy) {
    this->pika = pika;
}

void BoxSlot::draw() {
    std::vector<Drawable*> elements;
    
    //Draw texture
    Drawable* maintexture = new Drawable(texture, posx, posy);
    elements.push_back(maintexture);
    
    //Draw pokemon nickname
    const std::string FONTPATH = ExtDataManager::getBasePath() + "/fonts/roboto.ttf";
    const int XNICKPOS = posx + 50;
    const int YNICKPOS = posy + 5;
    Text* nicktext = new Text(FontManager::getFont(FONTPATH), XNICKPOS, YNICKPOS, 9, Text::BLACK, pika.getNickname());
    elements.push_back(nicktext);
    
    //Draw pokemon sprite
    const int SPRITEWIDTH = 40;
    const int SPRITEHEIGHT = 30;
    const std::string SPRITEPATH = ExtDataManager::getBasePath() + "/textures/pkmsprites.png";
    
    int spritesheetx;
    int spritesheety;
    if( !pika.isEgg() ) {
        spritesheetx = ((pika.getPokedexNumber() - 1) % 25) * SPRITEWIDTH;
        spritesheety = ((pika.getPokedexNumber() - 1) / 25) * SPRITEHEIGHT;
    }
        
    else {
        spritesheetx = (721 % 25) * SPRITEWIDTH;
        spritesheety = (721 / 25) * SPRITEHEIGHT;
    }
    
    Drawable* pokemontex = new Drawable(TextureManager::getTexture(SPRITEPATH), posx, posy, spritesheetx, spritesheety, SPRITEWIDTH, SPRITEHEIGHT);
    elements.push_back(pokemontex);
    
    //Draw bag icon
    if( pika.getItem() > 0 ) {
        const std::string BAGPATH = ExtDataManager::getBasePath() + "/textures/bag.png";
        const int XBAGPOS = posx + 25;
        const int YBAGPOS = posy + 20;
            
        Drawable* bag = new Drawable(TextureManager::getTexture(BAGPATH), XBAGPOS, YBAGPOS);
        elements.push_back(bag);
    }
    
    if( pika.isShiny() ) {
            const std::string SHINYPATH = ExtDataManager::getBasePath() + "/textures/shiny.png";
            const int XSHINYPOS = posx + 60;
            const int YSHINYPOS = posy + 20;

            Drawable* shiny = new Drawable(TextureManager::getTexture(SHINYPATH), XSHINYPOS, YSHINYPOS);
            elements.push_back(shiny);
        }
    
    //Draw Pokemon level
    const int XLEVELPOS = posx + 75;
    const int YLEVELPOS = posy + 20;
        
    Drawable* leveltext = new Text(FontManager::getFont(FONTPATH), XLEVELPOS, YLEVELPOS, 9, Text::BLACK, ExtDataManager::getGuiText(ExtDataManager::LVSTRING)+" "+intTOstring(pika.getLevel(), 10));
    elements.push_back(leveltext);
    
    for(unsigned int i = 0; i < elements.size(); i++)
        elements[i]->draw();
    
    for(unsigned int i = 0; i < elements.size(); i++)
        delete elements[i];
}
