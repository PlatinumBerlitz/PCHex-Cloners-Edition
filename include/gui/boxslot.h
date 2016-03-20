#ifndef BOXSLOT_H
#define BOXSLOT_H

#include "drawable.h"
#include "pokemon.h"

class BoxSlot : public Drawable {
    private:
        Pokemon pika;
        
    public:
        BoxSlot(raw_texture* tex, const int posx, const int posy, Pokemon pika);
        virtual void draw();
};

#endif /* BOXSLOT_H */

