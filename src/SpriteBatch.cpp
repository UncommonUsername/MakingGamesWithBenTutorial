#include "SpriteBatch.h"

SpriteBatch::SpriteBatch()
{

}

SpriteBatch::~SpriteBatch()
{

}

void SpriteBatch::init()
{

}

void SpriteBatch::begin()
{

}

void SpriteBatch::end()
{

}

void SpriteBatch::draw(const glm::vec4& destinationRextangle, const glm::vec4& uvRecrangle, GLuint texture, float depth, const Color& color)
{
    Glyph newGlyph;
    newGlyph.texture = texture;
    newGlyph.depth = depth;

    newGlyph.topLeft.color = color;
    newGlyph.topLeft.setPosition(destinationRextangle.x, destinationRextangle.y + uvRecrangle.w);
}

void SpriteBatch::renderBatch()
{

}