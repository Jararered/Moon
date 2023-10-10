#version 330 core

in vec3 v_Normal;

out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
    // Light
    vec3 lightDirection = vec3(0.333, -1.0, 0.666);
    float light = (dot(-1.0 * lightDirection, v_Normal) + 1.0) / 2.0;
    light = (light + 1.0) / 2.0;

    FragColor = vec4(light, light, light, 1.0);
}
