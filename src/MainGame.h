#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Sprite.h"
#include "GLSLProgram.h"
#include "GLTexture.h"
#include "Window.h"
#include "Camera2D.h"
#include "SpriteBatch.h"
#include "InputManager.h"
#include "Timer.h"

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

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cusros_por_callback(GLFWwindow* window, double xpos, double ypos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    Window _window;
    int _screenWidth;
    int _screenHeight;

    GameState _gameState;

    Camera2D _camera;

    GLSLProgram _colorProgram;
    SpriteBatch _spriteBatch;
    FpsLimiter _fpsLimiter;
    
    static InputManager _inputManager;

    float _fps;
    float _maxFPS;

};