#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Position;
in vec3 Normal;

uniform sampler2D diffuse;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float lightStrength;

uniform struct Material {
    vec4 color;
} material;

void main()
{
    vec3 lightDir = lightPosition - Position;
    vec3 normal = normalize(Normal);
    lightDir = normalize(lightDir);

    float diff = dot(normal, lightDir);
    diff = max(diff, 0.0);

    vec3 ambientColor = lightColor * lightStrength;
    vec3 diffuseColor = lightColor * diff;
    vec4 objectColor = material.color + texture(diffuse, TexCoord);

    FragColor = vec4(ambientColor, 1.0f) * objectColor + vec4(diffuseColor, 1.0f) * objectColor;
    //FragColor = objectColor;
}