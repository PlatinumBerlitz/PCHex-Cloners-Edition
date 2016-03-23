#include "editableoverlay.h"
#include "extdatamanager.h"
#include "text.h"

EditableOverlay::EditableOverlay(raw_texture* texture, const int selected, const std::string msg, std::vector<std::string> elements) : Overlay(texture, msg) {
    this->selected = selected;
    this->elementslist = elements;
}

void EditableOverlay::draw() {
    std::vector<Drawable*> elements;
    
    int i = 0;
    do {
        i++;
    }while((posy+20+10*i) < this->getDownBorder());
        
    int todraw = i;
        
    Drawable* menu = new Drawable(texture, posx, posy);
    elements.push_back(menu);
    
    const std::string FONTPATH = ExtDataManager::getBasePath() + "/fonts/roboto_bold.ttf";
    const int XMSGPOS = posx + 10;
    const int YMSGPOS = posy + 10;
    Text* text = new Text(FontManager::getFont(FONTPATH), XMSGPOS, YMSGPOS, 9, Text::BLACK, msg);
    elements.push_back(text);
    
    int start = selected / todraw;
    int j = 0;
    for(unsigned int i = (start*todraw); i < elementslist.size() && j < todraw ; i++) {
        const int STRINGMAX = 26;
        std::string towrite;
        if( elementslist[i].size() > STRINGMAX )
            towrite = elementslist[i].substr(0, STRINGMAX) + "...";
            
        else towrite = elementslist[i]; 
        //if( posx+5+sftd_get_text_width(font, 6, towrite.c_str()) >= this->getRightBorder() ) towrite = towrite.substr(0, 12) + "...";
        int color;
        if( selected == i ) color = Text::WHITE; /*sftd_draw_text(font, posx+5, posy+10+(10*j), RGBA8(255, 255, 255, 255), 6, towrite.c_str());*/ 
        else color = Text::BLACK; /*sftd_draw_text(font, posx+5, posy+10+(10*j), RGBA8(0, 0, 0, 255), 6, towrite.c_str());*/
        Drawable* textlist = new Text(FontManager::getFont(FONTPATH), XMSGPOS, posy+20+(10*j), 9, color, towrite);
        elements.push_back(textlist);
        j++;
    }    
    
    
    for(unsigned int i = 0; i < elements.size(); i++)
        elements[i]->draw();
    
    for(unsigned int i = 0; i < elements.size(); i++)
        delete elements[i];
}

int EditableOverlay::getDownBorder() {
    return posy + texture->height - 17;
}