#include "graphic.h"

int Graphic::startGraphicEnviroment() {
    if( !sf2d_init() )
        return 0x211;
    
    if( !sftd_init() )
        return 0x212;
    
    return 0;
}

void Graphic::startFrame(const int screen) {
    if( screen == TOPSCREEN )
        sf2d_start_frame(GFX_TOP, GFX_LEFT);
    
    else sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
}

void Graphic::endFrame() {
    sf2d_end_frame();
}
void Graphic::swapbuffer() {
    sf2d_swapbuffers();
}

void Graphic::closeGraphicEnviroment() {
    TextureManager::freeAllTextures();
    FontManager::freeAllFonts();
    sftd_fini();
    sf2d_fini();
}
