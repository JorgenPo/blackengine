#version 330

in  vec2 fTexCoords;
out vec4 finColor;

uniform sampler2D textureSampler;

void main(void)
{
    finColor = texture(textureSampler, fTexCoords);
}
