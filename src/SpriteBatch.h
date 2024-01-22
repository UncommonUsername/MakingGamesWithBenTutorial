#pragma once
#include <GL/glew.h>
#include <vector>

#include "glm/glm.hpp"
#include "Vertex.h"

enum class GlyphSortType
{
    NONE,
    FRONT_TO_BACK,
    BACK_TO_FRONT,
    TEXTURE
};

struct Glyph
{
    GLuint texture;
    float depth;

    Vertex topLeft;
    Vertex topRight;
    Vertex bottomLeft;
    Vertex bottomRight;
};

class RenderBatch
{
public:
    RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : 
        offset(Offset),
        numVertices(NumVertices),
        texture(Texture){}
    GLuint offset;
    GLuint numVertices;
    GLuint texture;
};

class SpriteBatch
{
public:
    SpriteBatch();
    ~SpriteBatch();

    void init();

    void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
    void end();

    void draw(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle, GLuint texture, float depth, const Color& color);

    void renderBatch();

private:
    void createRenderBatches();
    void createVertexArray();
    void sortGlyph();

    static bool compareFrontToBack(Glyph* a, Glyph* b);
    static bool compareBackToFront(Glyph* a, Glyph* b);
    static bool compareTexture(Glyph* a, Glyph* b);

    GLuint _vbo, _vao;

    GlyphSortType _sortType;

    std::vector<Glyph*> _glyphs;
    std::vector<RenderBatch> _renderBatch;
};