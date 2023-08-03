#version 330 core

in vec3 v_Color;
in vec4 v_RotatedNormal;

out vec4 FragColor;

void main()
{
    vec3 lightDirection = vec3(1.0, -1.0, 1.0);

    // 0.0 to 1.0
    float dotProduct = dot(v_RotatedNormal.xyz, -1.0 * lightDirection);

    // 0.5 to 1.0
    float brightness = (dotProduct + 1) / 2; 

    FragColor = vec4((v_Color * brightness), 1.0);
}
