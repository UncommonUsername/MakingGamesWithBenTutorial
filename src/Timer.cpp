#include "Timer.h"
#include "GLFW/glfw3.h"

FpsLimiter::FpsLimiter()
{
}

void FpsLimiter::init(float targetFPS)
{
    setTargetFPS(targetFPS);
}

void FpsLimiter::setTargetFPS(float targetFPS)
{
    _maxFPS = targetFPS;
}

void FpsLimiter::begin()
{
    _startTicks = glfwGetTime();
}

float FpsLimiter::end()
{
    calculateFPS();

    // Get ticks in miliseconds 
    _frameTicks = glfwGetTime() - _startTicks;

    // Delay program to limit FPS
    while (1.0f / _maxFPS > _frameTicks)
    {
        _frameTicks = glfwGetTime() - _startTicks;
    }

    return _fps;
}

void FpsLimiter::calculateFPS()
{
    static const int NUM_SAMPLES = 10;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;

    // Multiplied by 1000 to change it from seconds to milisecond.
    static float previousTicks = glfwGetTime();

    float currentTicks;
    currentTicks = glfwGetTime();

    _frameTicks = currentTicks - previousTicks;
    frameTimes[currentFrame % NUM_SAMPLES] = _frameTicks;

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
        _fps = 1.0f / frameTimeAverage;
    }
    else
    {
        _fps = 60.0f;
    }
}
