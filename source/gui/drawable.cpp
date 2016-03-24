#include "drawable.h"

Drawable::Drawable(raw_texture* texture, const int posx, const int posy) {
    this->texture = texture;
    this->posx = posx;
    this->posy = posy;
    this->partx = 0;
    this->party = 0;
    this->partw = 0;
    this->parth = 0;
    active = false;
    this->id = NOID;
}

Drawable::Drawable(raw_texture* texture, const int posx, const int posy, const int partx, const int party, const int partw, const int parth) {
    this->texture = texture;
    this->posx = posx;
    this->posy = posy;
    this->partx = partx;
    this->party = party;
    this->partw = partw;
    this->parth = parth;
    active = false;
    this->id = NOID;
}

Drawable::Drawable(raw_texture* texture, const int posx, const int posy, bool active, const int id) {
    this->texture = texture;
    this->posx = posx;
    this->posy = posy;
    this->partx = 0;
    this->party = 0;
    this->partw = 0;
    this->parth = 0;
    this->active = active;
    this->id = id;
    
}

void Drawable::draw() {
    if(partw && parth)
        sf2d_draw_texture_part(texture, posx, posy, partx, party, partw, parth);
    
    else sf2d_draw_texture(texture, posx, posy);
}

int Drawable::isTouched(const touchPosition& touch) {
    if( active && ((touch.px > posx && touch.px < posx+texture->width) && (touch.py > posy && touch.py < posy+texture->height)) )
        return id;
    
    return NOID;
}