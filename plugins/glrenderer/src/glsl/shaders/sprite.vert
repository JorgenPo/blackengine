#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

uniform vec3 cameraPosition;

void main()
{
    mat4 viewModel = view * model;

    // Cylindric billboarding
    viewModel[0][0] = 5;
    viewModel[0][1] = 0;
    viewModel[0][2] = 0;

    viewModel[1][0] = 0;
    viewModel[1][1] = 5;
    viewModel[1][2] = 0;

    viewModel[2][0] = 0;
    viewModel[2][1] = 0;
    viewModel[2][2] = 5;

    vec4 pos = viewModel * vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
    gl_Position = projection * pos;

    TexCoord = aTexCoord;
}