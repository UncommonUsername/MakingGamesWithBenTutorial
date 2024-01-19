#include "Window.h"
#include "Errors.h"

#include <iostream>

Window::Window()
{

}

Window::~Window()
{

}

int Window::createWindow(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
{
    // TODO: Use flags to set fullscreen on of off.

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
    _window = glfwCreateWindow(screenWidth, screenHeight, windowName.c_str(), NULL, NULL);

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

    std::printf("*** OpenGL Version: %s ***", glGetString(GL_VERSION));

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.012f, 0.0235f, 0.2157f, 1.0f);

    return 0;
}

void Window::mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    std::cout << xposIn << " " << yposIn << std::endl;
}

bool Window::windowShouldClose()
{
    return glfwWindowShouldClose(_window);
}

void Window::swapBuffers()
{
    glfwSwapBuffers(_window);
}