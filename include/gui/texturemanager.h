#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <string>
#include <sf2d.h>

typedef sf2d_texture raw_texture;

class TextureManager {
    private:
        static const unsigned int INVALID_PATH = 0;
        static const unsigned int JPEG = 1;
        static const unsigned int PNG = 2;
        static const unsigned int BMP = 3;
        
        static std::map<std::string, raw_texture*> texturemap;
        
        static void addNewTexture(const std::string path);
        static raw_texture* loadFromFile(const std::string path);
        static unsigned int getExtension(const std::string path);
        
        
    public:
        static raw_texture* getTexture(const std::string path);
        static void freeAllTextures();
};

#endif 

