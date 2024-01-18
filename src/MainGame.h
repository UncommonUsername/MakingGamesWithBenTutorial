#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Sprite.h"
#include "GLSLProgram.h"
#include "GLTexture.h"

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
    void calculateFPS();

    static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);

    GLFWwindow* _window;
    int _screenWidth;
    int _screenHeight;

    GameState _gameState;

    std::vector<Sprite*> _sprite;

    GLSLProgram _colorProgram;

    float _fps;
    float _frameTime;
    float _time;
};