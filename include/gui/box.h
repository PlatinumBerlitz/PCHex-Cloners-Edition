#ifndef BOX_H
#define BOX_H

#include "drawable.h"

class Box : public Drawable {
    public:
        Box(const int posx, const int posy);
        
        virtual void draw();
};

#endif /* BOX_H */

