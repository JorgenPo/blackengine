#version 330

in vec3 vPosition;
in vec2 vTexCoords;

uniform mat4 mMatrix;

out vec2 fTexCoords;

void main(void)
{
    gl_Position = mMatrix * vec4(vPosition, 1.0);
}
