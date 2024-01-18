#pragma once
#include <GL/glew.h>
#include "GLTexture.h"

class Sprite
{
public:
    Sprite();
    ~Sprite();

    void init(float x, float y, float width, float height, const char* filePath);

    void draw();

private:
    float _x;
    float _y;
    float _width;
    float _height;
    GLuint _vboId;
    GLuint _vaoId;

    GLTexture _texture;
};