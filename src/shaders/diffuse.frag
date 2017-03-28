#version 330

/* Attributes (interpolated) */
in  vec2 fTexCoords;

/* Result - color */
out vec4 finColor;

/* Textures */
uniform sampler2D textureSampler;

void main(void)
{
    finColor = texture(textureSampler, fTexCoords);
}
