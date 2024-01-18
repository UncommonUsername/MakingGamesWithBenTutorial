#include "ResourceManager.h"

TextureCache ResourceManager::_textureCache;

GLTexture ResourceManager::getTexture(const char* texturePath)
{
    return _textureCache.getTexture(texturePath);
}