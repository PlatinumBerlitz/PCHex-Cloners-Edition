#ifndef FIELD_H
#define FIELD_H

#include <string>

#include "drawable.h"

class Field : public Drawable {
    private:
        std::string label;
        std::string textfield;
        int mode;
        
    public:
        static const int POKEBALLMODE = 0;
        static const int ARROWMODE = 1;
        
        Field(raw_texture* texture, const int posx, const int posy, const bool active, const int id, const std::string label, const std::string textfield, const int mode);
        
        virtual void draw();
        virtual int isTouched(const touchPosition& touch);
};

#endif /* FIELD_H */

