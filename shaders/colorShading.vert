#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 vecColor;

out vec4 fragColor;

void main()
{
    gl_Position.xy = aPos;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;

    fragColor = vecColor;
}