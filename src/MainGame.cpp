#include "MainGame.h"
#include "Errors.h"
#include "ResourceManager.h"

#include <iostream>
#include <string>

InputManager MainGame::_inputManager;

MainGame::MainGame() :
    _screenWidth(1026),
    _screenHeight(768),
    _gameState(GameState::PLAY),
    _maxFPS(60)
{
    _camera.init(_screenWidth, _screenHeight);
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
    _window.createWindow("Game Engine", _screenWidth, _screenHeight, 0);

    glfwSetKeyCallback(_window.getWindow(), key_callback);
    glfwSetCursorPosCallback(_window.getWindow(), cusros_por_callback);

    initShaders();
    _spriteBatch.init();
    _fpsLimiter.init(_maxFPS);
}

void MainGame::initShaders()
{
    _colorProgram.compileShaders("./resources/shaders/colorShading.vert", "./resources/shaders/colorShading.frag");
    _colorProgram.addAttribute(3);
    _colorProgram.linkShaders();
}

void MainGame::processInput()
{

    float CAMERA_SPEED = 2.0f;

    glfwPollEvents();

    // Check if user pressed the X of the window
    if (_window.windowShouldClose())
    {
        _gameState = GameState::EXIT;
    }

    // Process keyboard input
    if (_inputManager.isKeyDown(GLFW_KEY_W))
    {
        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, - CAMERA_SPEED));
    }

    if (_inputManager.isKeyDown(GLFW_KEY_S))
    {
        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
    }

    if (_inputManager.isKeyDown(GLFW_KEY_A))
    {
        _camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
    }

    if (_inputManager.isKeyDown(GLFW_KEY_D))
    {
        _camera.setPosition(_camera.getPosition() + glm::vec2(- CAMERA_SPEED, 0.0f));
    }
}

void MainGame::gameLoop()
{
    while (_gameState != GameState::EXIT)
    {
        // Variables for limiting the FPS
        _fpsLimiter.begin();
        static int frameCount = 0;

        processInput();

        // Move camera and draw sprites to screen
        _camera.update();
        drawGame();

        _fps = _fpsLimiter.end();

        // Print FPS every 10 frames
        frameCount++;
        if (frameCount == 10)
        {
            // std::cout << _fps << std::endl;
            frameCount = 0;
        }
    }
}

void MainGame::drawGame()
{
    // Clear depth and color buffers
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use shaders
    _colorProgram.use();

    // Send player texture to shader
    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = _colorProgram.getUniformLocation("playerTexture");
    glUniform1i(textureLocation, 0);

    // Send projection matrix to shader
    GLuint pLocation = _colorProgram.getUniformLocation("P");
    glm::mat4 cameraMatrix = _camera.getCameraMathix();
    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

    _spriteBatch.begin();
    
    glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

    static GLTexture texture = ResourceManager::getTexture("./resources/textures/trex.png");

    Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

    _spriteBatch.draw(pos, uv, texture.id, 0.0f, color);

    _spriteBatch.end();
    _spriteBatch.renderBatch();

    glBindTexture(GL_TEXTURE_2D, 0);
    _colorProgram.unuse();

    _window.swapBuffers();
}

void MainGame::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << std::endl;
    if (action == 1 || action == 2)
    {
        _inputManager.pressKey(key);
    }
    else if (action == 0)
    {
        _inputManager.releaseKey(key);
    }
}

void MainGame::cusros_por_callback(GLFWwindow* window, double xpos, double ypos)
{
    std::cout << xpos << "-" << ypos << std::endl;
}