#version 330 core 

in vec4 fragColor;

out vec4 color;

uniform float time;

void main()
{
    color = fragColor + vec4(0.0, 0.0, 1.0 * cos(time), 0.0);
}