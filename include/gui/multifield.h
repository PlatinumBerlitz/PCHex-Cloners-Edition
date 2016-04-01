#ifndef MULTIFIELD_H
#define MULTIFIELD_H

#include <string>

#include "field.h"

class MultiField : public Field {
    private:
        std::string textfield2;
        std::string textfield3;
        int id2;
    
    public:
        MultiField(raw_texture* texture, const int posx, const int posy, const bool active, const int id, const int id2, const std::string label, const std::string textfield, const std::string textfield2, const std::string textfield3);
        virtual void draw();
        
        virtual int isTouched(const touchPosition& touch);
};

#endif /* MULTIFIELD_H */

