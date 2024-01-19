#include "ImageLoader.h"
#include "Errors.h"
#define STBI_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLTexture ImageLoader::loadPNG(const char* filePath)
{
    GLTexture texture = {};

    // Flip texture upsidedown so when printing is the right direction
    stbi_set_flip_vertically_on_load(true);

    // Load image data
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filePath, &width, &height, &nrChannels, 0);

    // Check if image data was loaded correctly
    if (!data)
    {
        fatalError("Failed to load texture!");
    }

    texture.width = width;
    texture.height = height;

    // Generate and bind texture data
    glGenTextures(1, &(texture.id));
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}