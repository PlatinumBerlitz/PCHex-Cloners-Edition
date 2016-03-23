#ifndef OVERLAY_H
#define OVERLAY_H

#include "drawable.h"

class Overlay : public Drawable {
    protected:
        std::string msg;
        
    public:
        Overlay(raw_texture* texture, const std::string msg);
        
        virtual void draw();
};

#endif /* OVERLAY_H */

