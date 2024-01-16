#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Sprite.h"
#include "GLSLProgram.h"

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
    MainGame();
    ~MainGame();

    void run();


private:
    void initSystems();
    void initShaders();
    void processInput();
    void gameLoop();
    void drawGame();

    static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);

    GLFWwindow* _window;
    int _screenWidth;
    int _screenHeight;

    GameState _gameState;

    Sprite _sprite;
    GLSLProgram _colorProgram;
};