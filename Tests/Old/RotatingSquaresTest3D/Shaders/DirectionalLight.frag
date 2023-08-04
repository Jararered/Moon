#version 330 core

in vec3 v_Color;
in vec4 v_RotatedNormal;

out vec4 FragColor;

void main()
{
    vec3 lightDirection = vec3(0.0, 1.0, 0.0);

    // 0 to 1
    float lightBrightness = (dot(v_RotatedNormal.xyz, lightDirection) + 1) / 2;

    // 0.5 to 1.0
    lightBrightness = (lightBrightness * 10.0 + 1.0) / 10.0;

    FragColor = vec4((v_Color * lightBrightness), 1.0);
}
