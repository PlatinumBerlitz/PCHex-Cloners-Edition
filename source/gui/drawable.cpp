#include "drawable.h"

Drawable::Drawable(raw_texture* texture, const int posx, const int posy) {
    this->texture = texture;
    this->posx = posx;
    this->posy = posy;
    this->partx = 0;
    this->party = 0;
    this->partw = 0;
    this->parth = 0;
}

Drawable::Drawable(raw_texture* texture, const int posx, const int posy, const int partx, const int party, const int partw, const int parth) {
    this->texture = texture;
    this->posx = posx;
    this->posy = posy;
    this->partx = partx;
    this->party = party;
    this->partw = partw;
    this->parth = parth;
}

void Drawable::draw() {
    if(partw && parth)
        sf2d_draw_texture_part(texture, posx, posy, partx, party, partw, parth);
    
    else sf2d_draw_texture(texture, posx, posy);
}
