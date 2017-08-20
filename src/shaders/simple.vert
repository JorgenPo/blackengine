#version 330

/* Attributes */
in vec3 vPosition;
in vec2 vTexCoords;
in vec3 vNormal;

/* Matrices */
uniform mat4 mModel;

/* Camera */
uniform mat4 mView;
uniform mat4 mPerspective;
uniform vec3 cameraPos;

/* Light */
uniform vec3 lightPosition;

out vec2 fTexCoords;
out vec3 surfaceNormal;
out vec3 toLightVec;
out vec3 toCameraVec;

void main(void)
{
    gl_Position = mPerspective * mView * mModel * vec4(vPosition, 1.0);
    fTexCoords = vTexCoords;

    toLightVec = (mModel * vec4(lightPosition - vPosition, 0)).xyz;
    toCameraVec = (mModel * vec4(cameraPos - vPosition, 0)).xyz;
    surfaceNormal = (mModel * vec4(vNormal, 0)).xyz;
}
