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

uniform vec3 colorMask;

uniform struct Light {
    bool enabled;
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

vec3 calculateDiffuseColor(vec3 normal, vec3 lightDir) {
    float diffuseFactor = max(dot(normal, lightDir), 0.0) * light.diffuseIntensity;
    return light.color * diffuseFactor;
}

vec3 calculateSpectacularColor(vec3 normal, vec3 lightDir) {
    vec3 reflectedDir = normalize(reflect(-lightDir, normal));
    vec3 fragmentToCamera = normalize(cameraPosition - Position);
    float spectacularFactor = pow(max(0.0, dot(fragmentToCamera, reflectedDir)), material.spectacularFactor);
    return light.diffuseIntensity * light.spectacularIntensity * light.color * 1.0f * spectacularFactor;
}

void main()
{
    vec3 toLightDir = -light.direction;
    vec3 normal = normalize(Normal);

    vec3 colorSum = ambientLight.color * ambientLight.intensity;

    if (light.enabled) {
        colorSum += calculateDiffuseColor(normal, toLightDir);
        colorSum += calculateSpectacularColor(normal, toLightDir);
    }

    vec4 objectColor = vec4(material.color, 1.0f) + texture(diffuse, TexCoord);

    FragColor = objectColor * vec4(colorSum, 1.0f) * vec4(colorMask, 1.0f);
    //    vec4 gamma = vec4(vec3(1.0/2.2), 1);
    //    FragColor = pow(FragColor, gamma); // gamma-corrected color
}