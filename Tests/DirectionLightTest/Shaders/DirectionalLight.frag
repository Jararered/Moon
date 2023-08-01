#version 330 core

in vec3 v_Color;
in vec4 v_RotatedNormal;

uniform vec3 u_LightPosition;
uniform vec3 u_LightDirection;

out vec4 FragColor;

void main()
{
    // vec3 lightDirection = vec3(0.0, 1.0, 0.0);
    // float brightness = (dot(v_Normal, lightDirection) + 1) / 2; // 0 to 1

    // 0 to 1
    float dotProduct = dot(v_RotatedNormal.xyz, -1.0 * u_LightDirection);
    float brightness = (dotProduct + 1) / 2; 

    FragColor = vec4((v_Color * brightness), 1.0);
}
