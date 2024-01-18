#include "TextureCache.h"
#include "ImageLoader.h"

TextureCache::TextureCache()
{

}

TextureCache::~TextureCache()
{

}

GLTexture TextureCache::getTexture(const char* texturePath)
{
    auto mit = _textureMap.find(texturePath);

    if (mit == _textureMap.end())
    {
        GLTexture newTexture = ImageLoader::loadPNG(texturePath);

        _textureMap.insert(std::make_pair(texturePath, newTexture));

        return newTexture;
    }

    return mit->second;
}