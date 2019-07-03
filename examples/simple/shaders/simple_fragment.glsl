#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Position;
in vec3 Normal;

uniform sampler2D diffuse;
uniform vec3 lightPosition;
uniform vec3 lightColor;

void main()
{
    float ambientStength = 0.6f;
    vec3 ambientColor = lightColor * ambientStength;

    FragColor = vec4(ambientColor, 1.0f) * texture(diffuse, TexCoord);
}