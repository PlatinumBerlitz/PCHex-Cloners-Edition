#include <sfil.h>

#include "texturemanager.h"

std::map<std::string, raw_texture*> TextureManager::texturemap;

raw_texture* TextureManager::getTexture(const std::string path) {
    std::map<std::string, raw_texture*>::iterator it = texturemap.find(path);
    
    if( it == texturemap.end() )
        addNewTexture(path);
    
    return texturemap.at(path);
}

void TextureManager::addNewTexture(const std::string path) {
    raw_texture* newtexture = loadFromFile(path);
    std::pair<std::string, raw_texture*> toadd(path, newtexture);
    texturemap.insert(toadd);
}

raw_texture* TextureManager::loadFromFile(const std::string path) {
    unsigned int extension = getExtension(path);
    
    if( extension ) {
        if( extension == JPEG )
             return sfil_load_JPEG_file(path.c_str(), SF2D_PLACE_RAM);
        
        else if( extension == PNG )
            return sfil_load_PNG_file(path.c_str(), SF2D_PLACE_RAM);
        
        else if( extension == BMP )
            return sfil_load_BMP_file(path.c_str(), SF2D_PLACE_RAM);
        
    }
    
    return nullptr;
}

unsigned int TextureManager::getExtension(const std::string path) {
    unsigned int index = path.find(".");
    
    if( index == std::string::npos )
        return INVALID_PATH;
    
    else {
        std::string extension = path.substr(index+1, 3);
        
        if( extension == "jpg" )
            return JPEG;
        
        else if( extension == "png" )
            return PNG;
        
        else if( extension == "bmp" )
            return BMP;
        
        else return INVALID_PATH;
    }
    
    return INVALID_PATH;
}

void TextureManager::freeAllTextures() {
    for(std::map<std::string, raw_texture*>::iterator it = texturemap.begin(); it != texturemap.end(); it++)
        sf2d_free_texture(it->second);
}