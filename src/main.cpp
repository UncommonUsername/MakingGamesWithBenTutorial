#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/gtc/type_ptr.hpp"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "MainGame.h"

int main(int argc, char** argv)
{
    MainGame mainGame;
    mainGame.run();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
