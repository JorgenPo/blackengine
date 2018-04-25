#version 330 core
out vec4 FragColor;

uniform float time;

void main()
{
    float pixelX = gl_FragCoord.x;
    float pixelY = gl_FragCoord.y;

    vec4 whiteColor = vec4(1.0, 1.0, 1.0, 1.0);
    vec4 blackColor = vec4(0.0, 0.0, 0.0, 1.0);

    if (mod(pixelX, 100) < 50 && mod(pixelY, 100) < 50) {
        FragColor = blackColor;
    } else if (mod(pixelX, 100) > 50 && mod(pixelY, 100) > 50) {
        FragColor = blackColor;
    } else {
        FragColor = whiteColor;
    }
}