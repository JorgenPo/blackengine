#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Position;
in vec3 Normal;

uniform sampler2D diffuse;

uniform struct {
    vec3 color;
    float strength;
} ambientLight;

uniform struct Light {
    vec3 position;
    vec3 color;
    vec3 direction;
    float strength;
} light;

uniform struct Material {
    vec3 color;
} material;

void main()
{
    vec3 lightDir = light.position - Position;
    vec3 normal = normalize(Normal);
    lightDir = normalize(lightDir);

    float diff = dot(normal, lightDir);
    diff = max(diff, 0.0) * light.strength;

    vec3 ambientColor = ambientLight.color * ambientLight.strength;
    vec3 diffuseColor = light.color * diff;
    vec4 objectColor = vec4(material.color, 1.0f) + texture(diffuse, TexCoord);

    FragColor = vec4(ambientColor, 1.0f) * objectColor + vec4(diffuseColor, 1.0f) * objectColor;
    //FragColor = objectColor;
}