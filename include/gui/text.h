#ifndef TEXT_H
#define TEXT_H

#include <string>

#include "fontmanager.h"
#include "drawable.h"

class Text : public Drawable {
    private:
        raw_font* font;
        int size;
        int color;
        bool wide;
        std::string msg;
        std::wstring wmsg;
        
    public:
        static const int WHITE = RGBA8(255, 255, 255, 255);
        static const int BLACK = RGBA8(0, 0, 0, 255);
        static const int RED = RGBA8(255, 0, 0, 255);
        
        Text(raw_font* font, const int posx, const int posy, const int size, const int color, std::string msg);
        Text(raw_font* font, const int posx, const int posy, const int size, const int color, std::wstring wmsg);
        
        virtual void draw();
};

#endif /* TEXT_H */

