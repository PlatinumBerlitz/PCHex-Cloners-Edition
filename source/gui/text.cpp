#include "texturemanager.h"
#include "text.h"

Text::Text(raw_font* font, const int posx, const int posy, const int size, const int color, std::string msg) : Drawable(nullptr, posx, posy) {
    this->size = size;
    this->color = color;
    this->wide = false;
    this->msg = msg;
    this->font = font;
}

Text::Text(raw_font* font, const int posx, const int posy, const int size, const int color, std::wstring wmsg) : Drawable(nullptr, posx, posy) {
    this->size = size;
    this->color = color;
    this->wide = true;
    this->wmsg = wmsg;
    this->font = font;
}

void Text::draw() {
    if(wide)
        sftd_draw_wtext (font, posx, posy, color, size, wmsg.c_str());
    
    else sftd_draw_text (font, posx, posy, color, size, msg.c_str());
}
