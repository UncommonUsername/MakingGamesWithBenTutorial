#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum class GameState {PLAY, EXIT};

class MainGame
{
public:
    MainGame();
    ~MainGame();

    void run();


private:
    void initSystems();
    void processInput();
    void gameLoop();

    static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);

    GLFWwindow* _window;
    int _screenWidth;
    int _screenHeight;

    GameState _gameState;
};