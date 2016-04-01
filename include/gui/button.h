#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include "drawable.h"

class Button : public Drawable {
    protected:
        int button;
        std::string msg;
        
    public:
        Button(raw_texture* texture, const int posx, const int posy, const int button, const std::string msg);
        
        virtual void draw();
};

#endif /* BUTTON_H */

