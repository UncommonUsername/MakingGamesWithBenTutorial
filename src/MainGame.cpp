#include "MainGame.h"
#include "Errors.h"

#include <iostream>
#include <string>

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

    _sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);

    gameLoop();
}

void MainGame::initSystems()
{
    // Initiate GLFW
    if (!glfwInit())
    {
        fatalError("GLFW failed to initiate!");
    }

    // GLFW configuration
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Window creation
    _window = glfwCreateWindow(_screenWidth, _screenHeight, "Game Engine", NULL, NULL);

    if (!_window)
    {
        glfwTerminate();
        fatalError("Failed to create window!");
    }

    glfwMakeContextCurrent(_window);
    glfwSetCursorPosCallback(_window, mouseCallback);

    // Initiate GLEW
    glewExperimental = GL_TRUE;
    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        glfwTerminate();
        fatalError("Failed to initialize GLEW!");
    }

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.012f, 0.0235f, 0.2157f, 1.0f);

    initShaders();
}

void MainGame::initShaders()
{
    _colorProgram.compileShaders("./shaders/colorShading.vert", "./shaders/colorShading.frag");
    _colorProgram.addAttribute();
    _colorProgram.linkShaders();
}

void MainGame::processInput()
{
    glfwPollEvents();

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
        drawGame();
    }
}

void MainGame::mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    std::cout << xposIn << " " << yposIn << std::endl;
};

void MainGame::drawGame()
{
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _colorProgram.use();

    _sprite.draw();

    _colorProgram.unuse();

    glfwSwapBuffers(_window);
}