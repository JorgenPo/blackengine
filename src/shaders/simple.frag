#version 330

/* Attributes (interpolated) */
in  vec2 fTexCoords;
in  vec3 surfaceNormal;

in  vec3 toLightVec;
in  vec3 toCameraVec;

/* Result - color */
out vec4 finColor;

/* Textures */
uniform sampler2D textureSampler;
uniform bool enableTextures;

/* Light */
struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 spectacular;
};

uniform Light light;

/* Material */
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 spectacular;
    float shineFactor;
};

uniform Material material;

void main(void)
{
    /* Ambient component */
    vec3 ambient = light.ambient * material.ambient;

    /* Diffuse component */
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitToLight = normalize(toLightVec);
    vec3 unitToCamera = normalize(toCameraVec);

    float diff = max(dot(unitNormal, unitToLight), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    /* Spectacular component */
    vec3 reflectedRay = reflect(-unitToLight, unitNormal);
    float spec = pow(max(dot(unitToCamera, reflectedRay), 0.0), material.shineFactor);
    vec3 spectacular = light.spectacular * (material.spectacular * spec);

    vec4 color = vec4(1.0);

    /* Final color */
    if ( enableTextures ) {
        color = texture(textureSampler, fTexCoords);
    }

    finColor = vec4(ambient + diffuse + spectacular, 1.0) * color;
}
