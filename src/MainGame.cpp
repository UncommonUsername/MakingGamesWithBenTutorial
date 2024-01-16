#include <iostream>

#include "MainGame.h"

MainGame::MainGame()
{
    _window = nullptr;
    _screenWidth = 1026;
    _screenHeight = 768;
    _gameState = GameState::PLAY;
}

MainGame::~MainGame()
{
    glfwTerminate();
}

void MainGame::run()
{
    initSystems();
    gameLoop();
}

void MainGame::initSystems()
{
    // Initiate GLFW
    if (!glfwInit())
    {
        std::cerr << "Error: Failed to initiate GLFW." << std::endl;
    }

    // GLFW configuration
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Window creation
    _window = glfwCreateWindow(_screenWidth, _screenHeight, "Game Engine", NULL, NULL);

    if (!_window)
    {
        std::cerr << "Error: Failed to create GLFW window." << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(_window);
    glfwSetCursorPosCallback(_window, mouseCallback);
}

void MainGame::processInput()
{
    if (glfwWindowShouldClose(_window))
    {
        _gameState = GameState::EXIT;
    }
}

void MainGame::gameLoop()
{
    while (_gameState != GameState::EXIT)
    {
        processInput();

        glfwSwapBuffers(_window);
        glfwPollEvents();
    }
}

void MainGame::mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    std::cout << xposIn << " " << yposIn << std::endl;
};