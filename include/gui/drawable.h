#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "texturemanager.h"

class Drawable {
    protected:
        raw_texture* texture;
        int posx;
        int posy;
        int partx;
        int party;
        int partw;
        int parth;
        
    public:
        Drawable(raw_texture* texture, const int posx, const int posy);
        Drawable(raw_texture* texture, const int posx, const int posy, const int partx, const int party, const int partw, const int parth);
        
        virtual void draw();
};

#endif /* DRAWABLE_H */

