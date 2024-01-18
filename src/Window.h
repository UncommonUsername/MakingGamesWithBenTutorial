#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

enum WindowFlags {INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4};

class Window
{
public:
    Window();
    ~Window();

    int createWindow(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

    int getScreenWidth() {return _screenWidth;}
    int getScreenHeight() {return _screenHeight;}

    bool windowShouldClose();
    void swapBuffers();

    static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);

private:
    GLFWwindow* _window;
    int _screenWidth, _screenHeight;
};