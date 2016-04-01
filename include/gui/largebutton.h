#ifndef LARGEBUTTON_H
#define LARGEBUTTON_H

#include "button.h"

class LargeButton : public Button {
    public:
        LargeButton(raw_texture* texture, const int posx, const int posy, const int button, const std::string msg);
        
        virtual void draw();
};

#endif /* LARGEBUTTON_H */

