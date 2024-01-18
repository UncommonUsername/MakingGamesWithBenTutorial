#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>

Sprite::Sprite()
{
    _vboId = 0;
    _vaoId = 0;
}

Sprite::~Sprite()
{
    if (_vaoId != 0)
    {
        glDeleteVertexArrays(1, &_vaoId);
    }

    if (_vboId != 0)
    {
        glDeleteBuffers(1, &_vboId);
    }
}

void Sprite::init(float x, float y, float width, float height, const char* filePath)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;

    _texture = ResourceManager::getTexture(filePath);

    if (_vboId == 0)
    {
        glGenBuffers(1, &_vboId);
    }

    if (_vaoId == 0)
    {
        glGenVertexArrays(1, &_vaoId);
    }

    Vertex vertexData[6];

    // First triangle
    vertexData[0].setPosition(x + width, y + width);
    vertexData[0].setUV(1.0f, 1.0f);

    vertexData[1].setPosition(x, y + height);
    vertexData[1].setUV(0.0f, 1.0f);

    vertexData[2].setPosition(x, y);
    vertexData[2].setUV(0.0f, 0.0f);

    // Second triangle
    vertexData[3].setPosition(x, y);
    vertexData[3].setUV(0.0f, 0.0f);

    vertexData[4].setPosition(x + width, y);
    vertexData[4].setUV(1.0f, 0.0f);

    vertexData[5].setPosition(x + width, y + height);
    vertexData[5].setUV(1.0f, 1.0f);

    for (int i = 0; i < 6; i++)
    {
        vertexData[i].setColor(210, 69 + (i * 20), 69, 255);
    }

    glBindVertexArray(_vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, _vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
    glBindTexture(GL_TEXTURE_2D, _texture.id);

    glBindBuffer(GL_ARRAY_BUFFER, _vboId);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}