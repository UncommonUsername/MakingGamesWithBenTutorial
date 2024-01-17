#include "Sprite.h"
#include "Vertex.h"

#include <cstddef>

Sprite::Sprite()
{
    _vboId = 0;
    _vaoId = 0;
}

Sprite::~Sprite()
{
    if (_vboId != 0)
    {
        glDeleteBuffers(1, &_vboId);
    }
}

void Sprite::init(float x, float y, float width, float height)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;

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
    vertexData[0].position.x = x + width;
    vertexData[0].position.y = y + width;

    vertexData[1].position.x = x;
    vertexData[1].position.y = y + height;

    vertexData[2].position.x = x;
    vertexData[2].position.y = y;

    // Second triangle
    vertexData[3].position.x = x;
    vertexData[3].position.y = y;

    vertexData[4].position.x = x + width;
    vertexData[4].position.y = y;

    vertexData[5].position.x = x + width;
    vertexData[5].position.y = y + height;

    for (int i = 0; i < 6; i++)
    {
        vertexData[i].color.r = 210;
        vertexData[i].color.g = 69 + (i * 20);
        vertexData[i].color.b = 69;
        vertexData[i].color.a = 255;
    }

    glBindVertexArray(_vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, _vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
    glBindBuffer(GL_ARRAY_BUFFER, _vboId);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}