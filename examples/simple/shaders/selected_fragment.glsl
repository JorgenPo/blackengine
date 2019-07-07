#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Position;
in vec3 Normal;

uniform sampler2D diffuse;

uniform struct Material {
    vec3 color;
} material;

void main()
{
    vec4 objectColor = vec4(material.color, 1.0f) + texture(diffuse, TexCoord);

    FragColor = objectColor * vec4(1.0f, 0.0f, 0.0f, 1.0f);
}