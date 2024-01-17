#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 vecColor;
layout (location = 2) in vec2 vertUV;

out vec4 fragColor;
out vec2 fragUV;

void main()
{
    gl_Position.xy = aPos;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;

    fragColor = vecColor;
    fragUV = vertUV;
}