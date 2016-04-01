#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <3ds.h>

#include "texturemanager.h"

class Drawable {
    protected:
        const int NOID = 0;
        
        raw_texture* texture;
        int posx;
        int posy;
        int partx;
        int party;
        int partw;
        int parth;
        bool active;
        int id;
        
    public:
        Drawable(raw_texture* texture, const int posx, const int posy);
        Drawable(raw_texture* texture, const int posx, const int posy, const int partx, const int party, const int partw, const int parth);
        Drawable(raw_texture* texture, const int posx, const int posy, bool active, const int id);
        
        virtual int isTouched(const touchPosition& touch);
        
        virtual void draw();
        
        virtual ~Drawable() { }
};

#endif /* DRAWABLE_H */

