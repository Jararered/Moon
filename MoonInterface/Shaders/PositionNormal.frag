#version 330 core

in vec3 v_Normal;

out vec4 FragColor;

void main()
{
    // Light points down
    vec3 lightDirection = vec3(0.1, -1.0, 0.2);

    // 0 to 1
    float lightBrightness = (dot(-1.0 * lightDirection, v_Normal) + 1) / 2;
    // 0.5 to 1
    lightBrightness = (lightBrightness + 1.0) / 2;

    FragColor = vec4((vec3(1.0, 1.0, 1.0) * lightBrightness), 1.0);
}