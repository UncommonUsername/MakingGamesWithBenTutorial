#pragma once

class FpsLimiter
{
public:
    FpsLimiter();
    void init(float targetFPS);
    void setTargetFPS(float targetFPS);

    void begin();
    float end();

private:
    void calculateFPS();

    float _targetFPS;
    double _startTicks;
    float _fps;
    float _maxFPS;
    float _frameTicks;
};