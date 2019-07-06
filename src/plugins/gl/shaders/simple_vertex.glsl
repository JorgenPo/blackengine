#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 TexCoord;
out vec3 Position;
out vec3 Normal;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);

    Position = (model * vec4(pos, 1)).xyz;
    Normal = (model * vec4(normal, 0)).xyz;
    TexCoord = texCoord;
}