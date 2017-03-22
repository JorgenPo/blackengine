#version 330

in  vec2 fTexCoords;
in  vec3 surfaceNormal;
in  vec3 toLightVec;

out vec4 finColor;

uniform sampler2D textureSampler;
uniform vec3 fLightColor;

void main(void)
{
    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitToLight = normalize(toLightVec);

    float dotProd = dot(unitNormal, unitToLight);
    dotProd = max(dotProd, 0);

    vec3 diffuse = dotProd * fLightColor;

    finColor = vec4(diffuse, 1.0) * texture(textureSampler, fTexCoords);
}
