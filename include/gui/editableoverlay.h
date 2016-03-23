#ifndef EDITABLEOVERLAY_H
#define EDITABLEOVERLAY_H

#include <vector>
#include <string>

#include "overlay.h"

class EditableOverlay : public Overlay {
    private:
        unsigned int selected;
        std::vector<std::string> elementslist;
        
        int getDownBorder();
        
    public:
        EditableOverlay(raw_texture* texture, const int selected, const std::string msg, std::vector<std::string> elements);
        
        virtual void draw();
            
};

#endif /* EDITABLEOVERLAY_H */

