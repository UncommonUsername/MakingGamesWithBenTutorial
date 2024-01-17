#version 330 core 

in vec4 fragColor;
in vec2 fragUV;

out vec4 color;

uniform float time;
uniform sampler2D playerTexture;

void main()
{
    vec4 textureColor = texture(playerTexture, fragUV);
    color = (fragColor + vec4(0.0, 0.0, 1.0 * cos(time), 0.0)) * textureColor;
}