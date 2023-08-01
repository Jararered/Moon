#version 330 core

in vec3 v_Position;
in vec3 v_Color;
in vec4 v_RotatedNormal;

uniform vec3 u_LightPosition;
uniform vec3 u_LightDirection;

out vec4 FragColor;

void main()
{
    float dotProduct = dot(v_RotatedNormal.xyz,normalize(u_LightPosition - v_Position));
    float brightness = (dotProduct + 1) / 2; 

    FragColor = vec4((v_Color * brightness), 1.0);
}
