#version 330 core
layout (location = 0) in vec2 aPos;

void main()
{
    gl_Position.xy = aPos;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;
}