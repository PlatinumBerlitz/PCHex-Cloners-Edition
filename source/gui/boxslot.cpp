#include <vector>

#include "boxslot.h"
#include "extdatamanager.h"
#include "fontmanager.h"
#include "texturemanager.h"
#include "text.h"
#include "utility.h"
#include "state.h"

BoxSlot::BoxSlot(raw_texture* tex, const int posx, const int posy, Pokemon pika) : Drawable(tex, posx, posy) {
    this->pika = pika;
}

void BoxSlot::draw() {
    std::vector<Drawable*> elements;
    
    //Draw texture
    Drawable* maintexture = new Drawable(texture, posx, posy);
    elements.push_back(maintexture);
    
    if(pika.getPokedexNumber() > 0) {
        //Draw pokemon nickname
        const std::string FONTPATH = ExtDataManager::getBasePath() + "/fonts/roboto.ttf";
        const int XNICKPOS = posx + 50;
        const int YNICKPOS = posy + 5;
        Text* nicktext = new Text(FontManager::getFont(FONTPATH), XNICKPOS, YNICKPOS, 9, Text::BLACK, pika.getNickname());
        elements.push_back(nicktext);

        //Draw pokemon sprite
        std::string spritepath;
        const int SPRITEWIDTH = 40;
        const int SPRITEHEIGHT = 30;
        const std::string SPRITEPATH = ExtDataManager::getBasePath() + "/textures/pkmsprites.png";
        const std::string SHINYSPRITEPATH = ExtDataManager::getBasePath() + "/textures/pkmsprites_shiny.png";
        const std::string FORMSPRITEPATH = ExtDataManager::getBasePath() + "/textures/pkmsprites_form.png";
        const std::string SHINYFORMSPRITEPATH = ExtDataManager::getBasePath() + "/textures/pkmsprites_form_shiny.png";
        int spritesheetx;
        int spritesheety;
        
        if( pika.getForm() == 0 || pika.getPokedexNumber() == 664 || pika.getPokedexNumber() == 665 ) {
            if( pika.isShiny() ) spritepath = SHINYSPRITEPATH;
            else spritepath = SPRITEPATH;

            if( !pika.isEgg() ) {
                spritesheetx = ((pika.getPokedexNumber()) % 25) * SPRITEWIDTH;
                spritesheety = ((pika.getPokedexNumber()) / 25) * SPRITEHEIGHT;
            }

            else {
                spritesheetx = (722 % 25) * SPRITEWIDTH;
                spritesheety = (722 / 25) * SPRITEHEIGHT;
            }
        }

        else {
            if( pika.isShiny() ) spritepath = SHINYFORMSPRITEPATH;
            else spritepath = FORMSPRITEPATH;
            
            int tempindex = ExtDataManager::getSpriteFormData(pika.getPokedexNumber()) + (pika.getForm() - 1);
            //Workaround because of the wrong spritesheet(?)
            if( pika.getPokedexNumber() >= 621 )
                tempindex = tempindex+2;
            
            spritesheetx = (tempindex % 12) * SPRITEWIDTH;
            spritesheety = (tempindex / 12) * SPRITEHEIGHT;
        }
        
        Drawable* pokemontex = new Drawable(TextureManager::getTexture(spritepath), posx, posy, spritesheetx, spritesheety, SPRITEWIDTH, SPRITEHEIGHT);
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
    }
    
    //Draw clone tick
    Drawable* tick;
    if( (State::getMode() == State::CLONEMODE && State::getBoxCloneOrigin() == pika.getBoxNumber() && State::getIndexCloneOrigin() == pika.getIndexNumber()) || (State::getMode() == State::MULTIPLECLONEMODE && pika.getBoxNumber() == State::getBoxCloneOrigin()) ) {
        const std::string TICKPATH = ExtDataManager::getBasePath() + "/textures/box_tick.png";
        const int XTICKPOS = posx + 40;
        const int YTICKPOS = posy + 7;
        tick = new Drawable(TextureManager::getTexture(TICKPATH), XTICKPOS, YTICKPOS);
        elements.push_back(tick);
    }
    
    for(unsigned int i = 0; i < elements.size(); i++)
        elements[i]->draw();
    
    for(unsigned int i = 0; i < elements.size(); i++)
        delete elements[i];
}
