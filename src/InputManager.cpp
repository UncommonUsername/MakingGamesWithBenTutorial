#include "InputManager.h"

InputManager::InputManager() :
    _mouseCoords(0.0f)
{
}

InputManager::~InputManager()
{
}

void InputManager::pressKey(unsigned int keyId)
{
    _keyMap[keyId] = true;
}

void InputManager::releaseKey(unsigned int keyId)
{
    _keyMap[keyId] = false;
}

void InputManager::setMouseCoords(float x, float y)
{
    _mouseCoords.x = x;
    _mouseCoords.y = y;
}

bool InputManager::isKeyDown(unsigned int keyId)
{
    auto it = _keyMap.find(keyId);
    if (it != _keyMap.end())
    {
        return it->second;
    }

    return false;
}

glm::vec2 InputManager::getMouseCoords()
{
    return _mouseCoords;
}