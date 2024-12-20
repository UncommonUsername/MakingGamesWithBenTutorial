#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera2D
{
public:
    Camera2D();
    ~Camera2D();

    void init(int screenWidth, int screenHeight);

    void update();

    glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

    void setPosition(const glm::vec2& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
    void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true; }

    glm::vec2 getPosition() { return _position; }
    glm::mat4 getCameraMathix() { return _cameraMatrix; }
    float getScale() { return _scale; }

private:
    int _screenWidth;
    int _screenHeight;
    
    float _scale;
    glm::vec2 _position;
    glm::mat4 _cameraMatrix;
    glm::mat4 _orthoMatrix;

    bool _needsMatrixUpdate;
};