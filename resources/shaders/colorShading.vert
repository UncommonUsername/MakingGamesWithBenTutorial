#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 vecColor;
layout (location = 2) in vec2 vertUV;

out vec4 fragColor;
out vec2 fragUV;

uniform mat4 P;

void main()
{
    gl_Position.xy = (P * vec4(aPos, 0.0, 1.0)).xy;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;

    fragColor = vecColor;
    fragUV = vertUV;
}