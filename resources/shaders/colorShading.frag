#version 330 core 

in vec4 fragColor;
in vec2 fragUV;

out vec4 color;

uniform sampler2D playerTexture;

void main()
{
    vec4 textureColor = texture(playerTexture, fragUV);
    color = textureColor;
}