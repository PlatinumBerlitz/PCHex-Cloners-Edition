#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "texturemanager.h"
#include "fontmanager.h"

class Graphic {
    public:
        static const int TOPSCREENWIDTH = 400;
        static const int TOPSCREENHEIGHT = 240;
        static const int BOTTOMSCREENWIDTH = 320;
        static const int BOTTOMSCREENHEIGHT = 240;
        static const int TOPSCREEN = 0;
        static const int BOTTOMSCREEN = 1;
        
        static int startGraphicEnviroment();
        static void closeGraphicEnviroment();
        static void startFrame(const int screen);
        static void endFrame();
        static void swapbuffer();
};

#endif /* GRAPHIC_H */

