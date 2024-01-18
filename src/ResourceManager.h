#pragma once
#include "TextureCache.h"

#include <string>

class ResourceManager
{
public:
    
    static GLTexture getTexture(const char* texturePath);

private:
    static TextureCache _textureCache;
};