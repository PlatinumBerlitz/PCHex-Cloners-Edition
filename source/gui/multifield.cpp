#include "multifield.h"
#include "extdatamanager.h"
#include "text.h"
#include "utility.h"

MultiField::MultiField(raw_texture* texture, const int posx, const int posy, const bool active, const int id, const int id2, const std::string label, const std::string textfield, const std::string textfield2, const std::string textfield3) : Field(texture, posx, posy, active, id, label, textfield, Field::ARROWMODE) {
    this->textfield2 = textfield2;
    this->textfield3 = textfield3;
    this->id2 = id2;
}

void MultiField::draw() {
    std::vector<Drawable*> elements;
    const std::string FONTPATH = ExtDataManager::getBasePath() + "/fonts/roboto_bold.ttf";
    
    //Draw texture
    Drawable* tex = new Drawable(texture, posx, posy);
    elements.push_back(tex);
    
    //Draw label
    const int XLABELPOS = posx + 5;
    const int YLABELPOS = posy + (texture->height/2) - 3;
    const int FIELDDISTANCE = 35;
    const int EDITFIELDDISTANCE = 55;
    
    Text* labeltext = new Text(FontManager::getFont(FONTPATH), XLABELPOS, YLABELPOS, 9, Text::WHITE, label);
    elements.push_back(labeltext);
    
    if(!active) {
        const int XFIELD1POS = XLABELPOS + FIELDDISTANCE;
        const int XFIELD2POS = XLABELPOS + FIELDDISTANCE*2;
        const int XFIELD3POS = XLABELPOS + FIELDDISTANCE*3;

        Text* field1text = new Text(FontManager::getFont(FONTPATH), XFIELD1POS, YLABELPOS, 9, Text::WHITE, textfield);
        elements.push_back(field1text);
        
        Text* field2text = new Text(FontManager::getFont(FONTPATH), XFIELD2POS, YLABELPOS, 9, Text::WHITE, textfield2);
        elements.push_back(field2text);
        
        Text* field3text = new Text(FontManager::getFont(FONTPATH), XFIELD3POS, YLABELPOS, 9, Text::WHITE, textfield3);
        elements.push_back(field3text);
    }
    
    else {
        const std::string DOWNARROW = ExtDataManager::getBasePath() + "/textures/downarrow.png";
        const std::string UPARROW = ExtDataManager::getBasePath() + "/textures/uparrow.png";
        
        const int XFIELD1POS = XLABELPOS + 40;
        const int XFIELD1DOWNPOS = XFIELD1POS - TextureManager::getTexture(DOWNARROW)->width - 3;
        const int YFIELD1DOWNPOS = posy + 2;
        const int XFIELD1UPPOS = XFIELD1POS + /*getTextWidth(FontManager::getFont(FONTPATH), 9, textfield) +*/ 12;
        const int YFIELD1UPPOS = YFIELD1DOWNPOS;
        
        Text* field1text = new Text(FontManager::getFont(FONTPATH), XFIELD1POS, YLABELPOS, 9, Text::WHITE, textfield);
        elements.push_back(field1text);
        
        Drawable* field1down = new Drawable(TextureManager::getTexture(DOWNARROW), XFIELD1DOWNPOS, YFIELD1DOWNPOS);
        elements.push_back(field1down);
        
        Drawable* field1up = new Drawable(TextureManager::getTexture(UPARROW), XFIELD1UPPOS, YFIELD1UPPOS);
        elements.push_back(field1up);
        
        const int XFIELD2POS = XFIELD1POS + EDITFIELDDISTANCE;
        const int XFIELD2DOWNPOS = XFIELD2POS - TextureManager::getTexture(DOWNARROW)->width - 3;
        const int YFIELD2DOWNPOS = posy + 2;
        const int XFIELD2UPPOS = XFIELD2POS + /*getTextWidth(FontManager::getFont(FONTPATH), 9, textfield2)*/ + 17;
        const int YFIELD2UPPOS = YFIELD2DOWNPOS;
        
        Text* field2text = new Text(FontManager::getFont(FONTPATH), XFIELD2POS, YLABELPOS, 9, Text::WHITE, textfield2);
        elements.push_back(field2text);
        
        Drawable* field2down = new Drawable(TextureManager::getTexture(DOWNARROW), XFIELD2DOWNPOS, YFIELD2DOWNPOS);
        elements.push_back(field2down);
        
        Drawable* field2up = new Drawable(TextureManager::getTexture(UPARROW), XFIELD2UPPOS, YFIELD2UPPOS);
        elements.push_back(field2up);
    }
    
    for(unsigned int i = 0; i < elements.size(); i++) 
        elements[i]->draw();
    
    for(unsigned int i = 0; i < elements.size(); i++) 
        delete elements[i];
}

int MultiField::isTouched(const touchPosition& touch) {
    const int XLABELPOS = posx + 5;
    const int XFIELD1POS = XLABELPOS + 40;
    const std::string DOWNARROW = ExtDataManager::getBasePath() + "/textures/downarrow.png";
    const int XFIELD1DOWNPOS = XFIELD1POS - TextureManager::getTexture(DOWNARROW)->width - 3;
    const int YFIELD1DOWNPOS = posy + 2;
    const int EDITFIELDDISTANCE = 55;
    
    Drawable down1(TextureManager::getTexture(DOWNARROW), XFIELD1DOWNPOS, YFIELD1DOWNPOS, active, id);
    if( down1.isTouched(touch) )
        return id;
    
    const int XFIELD1UPPOS = XFIELD1POS + 12;
    const int YFIELD1UPPOS = YFIELD1DOWNPOS;
    const std::string UPARROW = ExtDataManager::getBasePath() + "/textures/uparrow.png";
    
    Drawable up1(TextureManager::getTexture(UPARROW), XFIELD1UPPOS, YFIELD1UPPOS, active, id);
    if( up1.isTouched(touch) )
        return id+6;
    
    const int XFIELD2POS = XFIELD1POS + EDITFIELDDISTANCE;
    const int XFIELD2DOWNPOS = XFIELD2POS - TextureManager::getTexture(DOWNARROW)->width - 3;
    const int YFIELD2DOWNPOS = posy + 2;
    
    Drawable down2(TextureManager::getTexture(DOWNARROW), XFIELD2DOWNPOS, YFIELD2DOWNPOS, active, id);
    if( down2.isTouched(touch) )
        return id2;
    
    const int XFIELD2UPPOS = XFIELD2POS + 17;
    const int YFIELD2UPPOS = YFIELD2DOWNPOS;
    
    Drawable up2(TextureManager::getTexture(UPARROW), XFIELD2UPPOS, YFIELD2UPPOS, active, id);
    if( up2.isTouched(touch) )
        return id2+6;
    
    return Drawable::NOID;
}