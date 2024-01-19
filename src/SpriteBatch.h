#pragma once
#include <GL/glew.h>
#include <vector>

#include "glm/glm.hpp"
#include "Vertex.h"

struct Glyph
{
    GLuint texture;
    float depth;

    Vertex topLeft;
    Vertex topRight;
    Vertex bottomLeft;
    Vertex bottomRight;
};

class SpriteBatch
{
public:
    SpriteBatch();
    ~SpriteBatch();

    void init();

    void begin();
    void end();

    void draw(const glm::vec4& destinationRextangle, const glm::vec4& uvRecrangle, GLuint texture, float depth, const Color& color);

    void renderBatch();

private:
    GLuint _vbo, _vao;

    std::vector<Glyph> _glyphs;
};