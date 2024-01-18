#include "MainGame.h"
#include "Errors.h"

#include <iostream>
#include <string>

MainGame::MainGame() :
    _window(nullptr),
    _screenWidth(1026),
    _screenHeight(768),
    _gameState(GameState::PLAY),
    _time(0)
{
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
    _sprite.back()->init(-1.0f, -1.0f, 1.0f, 1.0f, "./resources/textures/trex.png");

    _sprite.push_back(new Sprite());
    _sprite.back()->init(0.0f, -1.0f, 1.0f, 1.0f, "./resources/textures/trex.png");

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
    _colorProgram.compileShaders("./resources/shaders/colorShading.vert", "./resources/shaders/colorShading.frag");
    _colorProgram.addAttribute(3);
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
        _time += 0.01f;
        drawGame();
        calculateFPS();

        static int frameCount = 0;
        frameCount++;
        if (frameCount == 10)
        {
            std::cout << _fps << std::endl;
            frameCount = 0;
        }
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
    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = _colorProgram.getUniformLocation("playerTexture");
    glUniform1i(textureLocation, 0);

    GLuint timeLocation = _colorProgram.getUniformLocation("time");
    glUniform1f(timeLocation, _time);

    for (int i = 0; i < _sprite.size(); i++)
    {
        _sprite[i]->draw();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    _colorProgram.unuse();

    glfwSwapBuffers(_window);
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

    currentFrame++;
}