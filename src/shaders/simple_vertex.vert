#version 330

in vec3 vPosition;
in vec2 vTexCoords;
in vec3 vNormal;

uniform mat4 mMatrix;
uniform vec3 vLightPos;

out vec2 fTexCoords;
out vec3 surfaceNormal;
out vec3 toLightVec;

void main(void)
{
    gl_Position = mMatrix * vec4(vPosition, 1.0);
    fTexCoords = vTexCoords;

    toLightVec = vLightPos - vPosition;

    surfaceNormal = (mMatrix * vec4(vNormal, 0)).xyz;
}
