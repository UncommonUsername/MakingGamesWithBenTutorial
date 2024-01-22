#pragma once
#include <unordered_map>

#include "glm/glm.hpp"

class InputManager
{
public:
    InputManager();
    ~InputManager();

    void pressKey(unsigned int keyId);
    void releaseKey(unsigned int keyId);

    void setMouseCoords(float x, float y);
    glm::vec2 getMouseCoords();

    bool isKeyDown(unsigned int keyId);

private:
    std::unordered_map<unsigned int, bool> _keyMap;
    glm::vec2 _mouseCoords;
};