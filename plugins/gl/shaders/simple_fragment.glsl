#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Position;
in vec3 Normal;

uniform sampler2D diffuse;
uniform vec3 cameraPosition;

uniform struct {
    vec3 color;
    float intensity;
} ambientLight;

uniform struct Light {
    vec3 position;
    vec3 color;
    vec3 direction;
    float diffuseIntensity;
    float spectacularIntensity;
} light;

uniform struct Material {
    vec3 color;
    float spectacularFactor;
} material;

void main()
{
    vec3 lightDir = normalize(light.position - Position);
    vec3 fragmentToCamera = normalize(cameraPosition - Position);
    vec3 normal = normalize(Normal);

    float diffuseFactor = max(dot(normal, lightDir), 0.0) * light.diffuseIntensity;

    vec3 reflectedDir = normalize(reflect(-lightDir, normal));
    float spectacularFactor = pow(max(0.0, dot(fragmentToCamera, reflectedDir)), material.spectacularFactor);

    vec3 ambientColor = ambientLight.color * ambientLight.intensity;
    vec3 diffuseColor = light.color * diffuseFactor;
    vec4 objectColor = vec4(material.color, 1.0f) + texture(diffuse, TexCoord);
    vec3 spectacularColor = light.spectacularIntensity * light.color * 1.0f * spectacularFactor;

    FragColor = objectColor * vec4(ambientColor + diffuseColor + spectacularColor, 1.0f);
//    vec4 gamma = vec4(vec3(1.0/2.2), 1);
//    FragColor = pow(FragColor, gamma); // gamma-corrected color
}