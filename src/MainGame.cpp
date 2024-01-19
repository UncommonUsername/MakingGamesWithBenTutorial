#include "MainGame.h"
#include "Errors.h"

#include <iostream>
#include <string>

MainGame::MainGame() :
    _screenWidth(1026),
    _screenHeight(768),
    _gameState(GameState::PLAY),
    _time(0),
    _maxFPS(60)
{
    _camera.init(_screenWidth, _screenHeight);
}

MainGame::~MainGame()
{
    while (!_sprite.empty())
    {
        delete _sprite.back();
        _sprite.pop_back();
    }

    glfwTerminate();
}

void MainGame::run()
{
    initSystems();

    _sprite.push_back(new Sprite());
    _sprite.back()->init(0.0f, 0.0f, _screenWidth / 3, _screenWidth / 3, "./resources/textures/trex.png");

    gameLoop();
}

void MainGame::initSystems()
{
    _window.createWindow("Game Engine", _screenWidth, _screenHeight, 0);
    initShaders();
}

void MainGame::initShaders()
{
    _colorProgram.compileShaders("./resources/shaders/colorShading.vert", "./resources/shaders/colorShading.frag");
    _colorProgram.addAttribute(3);
    _colorProgram.linkShaders();
}

void MainGame::processInput()
{

    const float CAMERA_SPEED = 10.0f;

    if (_window.windowShouldClose())
    {
        _gameState = GameState::EXIT;
    }

    if (glfwGetKey(_window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, - CAMERA_SPEED));
    }

    glfwPollEvents();

    if (glfwGetKey(_window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
    {
        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
    }

    if (glfwGetKey(_window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        _camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
    }

    if (glfwGetKey(_window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        _camera.setPosition(_camera.getPosition() + glm::vec2(- CAMERA_SPEED, 0.0f));
    }
}

void MainGame::gameLoop()
{
    while (_gameState != GameState::EXIT)
    {
        double startTicks = glfwGetTime() * 1000;

        processInput();
        _time += 0.01f;

        _camera.update();
        drawGame();
        calculateFPS();

        static int frameCount = 0;
        frameCount++;
        if (frameCount == 10)
        {
            std::cout << _fps << std::endl;
            frameCount = 0;
        }

        double frameTicks = (glfwGetTime() * 1000) - startTicks;

        while (1000.0f / _maxFPS > frameTicks)
        {
            frameTicks = (glfwGetTime() * 1000) - startTicks;
        }
    }
}

void MainGame::drawGame()
{
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _colorProgram.use();

    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = _colorProgram.getUniformLocation("playerTexture");
    glUniform1i(textureLocation, 0);

    GLuint timeLocation = _colorProgram.getUniformLocation("time");
    glUniform1f(timeLocation, _time);

    GLuint pLocation = _colorProgram.getUniformLocation("P");
    glm::mat4 cameraMatrix = _camera.getCameraMathix();
    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

    for (int i = 0; i < _sprite.size(); i++)
    {
        _sprite[i]->draw();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    _colorProgram.unuse();

    _window.swapBuffers();
}

void MainGame::calculateFPS()
{
    static const int NUM_SAMPLES = 10;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;

    // Multiplied by 1000 to change it from seconds to milisecond.
    static float previousTicks = glfwGetTime() * 1000;

    float currentTicks;
    currentTicks = glfwGetTime() * 1000;

    _frameTime = currentTicks - previousTicks;
    frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

    previousTicks = currentTicks;

    int count;

    currentFrame++;

    if (currentFrame < NUM_SAMPLES)
    {
        count = currentFrame;
    }
    else
    {
        count = NUM_SAMPLES;
    }

    float frameTimeAverage = 0;
    for (int i = 0; i < count; i++)
    {
        frameTimeAverage += frameTimes[i];
    }
    frameTimeAverage /= count;

    if (frameTimeAverage > 0)
    {
        _fps = 1000.0f / frameTimeAverage;
    }
    else
    {
        _fps = 60.0f;
    }
}