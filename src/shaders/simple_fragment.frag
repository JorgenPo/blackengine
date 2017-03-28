#version 330

/* Attributes (interpolated) */
in  vec2 fTexCoords;
in  vec3 surfaceNormal;
in  vec3 toLightVec;

/* Result - color */
out vec4 finColor;

/* Textures */
uniform sampler2D textureSampler;

/* Light */
uniform vec3 fLightColor;

/* Material */
uniform vec3 matAmbient;
uniform vec3 matDiffuse;
uniform vec3 matSpectacular;

void main(void)
{
    /* Ambient component */
    //vec3 ambient = fLightColor * matAmbient;

    /* Diffuse component */
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitToLight = normalize(toLightVec);

    float diff = max(dot(unitNormal, unitToLight), 0.0);
    vec3 diffuse = diff * matDiffuse * fLightColor;

    /* Spectacular component */

    /* Final color */
    finColor = vec4(diffuse, 1.0) * texture(textureSampler, fTexCoords);
}
