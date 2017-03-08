#version 140
in vec3 vPosition;
in vec3 vColor;

out vec4 fColor;

void main(void)
{
    gl_Position = vec4(vPosition, 1.0);
    fColor = vec4(vColor, 1.0);
}
