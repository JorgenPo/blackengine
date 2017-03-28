#version 330

/* Attributes */
in vec3 vPosition;
in vec2 vTexCoords;

/* Matrices */
uniform mat4 mModel;
uniform mat4 mView;
uniform mat4 mPerspective;

/* Output */
out vec2 fTexCoords;

void main(void)
{
    gl_Position = mPerspective * mView * mModel * vec4(vPosition, 1.0);
    fTexCoords = vTexCoords;
}
