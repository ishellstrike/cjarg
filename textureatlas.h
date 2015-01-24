#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H
#include <string>
#include "jtexture.h"

class TextureAtlas
{
public:
    TextureAtlas();
    ~TextureAtlas();
    static Texture tex;

    void LoadAll(const std::string &a);
};

#endif // TEXTUREATLAS_H
