#version 330
in vec3 vPosition;
in vec3 vColor;

uniform mat4 mMatrix;
uniform vec3 lightPos;

out vec4 fColor;

void main(void)
{
    gl_Position = mMatrix * vec4(vPosition, 1.0);

    float dist = distance(lightPos, vPosition);

    fColor = vec4(vPosition, 1);
}
