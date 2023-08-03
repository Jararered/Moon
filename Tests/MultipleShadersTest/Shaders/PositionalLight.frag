#version 330 core

in vec3 v_Position;
in vec3 v_Color;
in vec4 v_RotatedNormal;

out vec4 FragColor;

void main()
{
    vec3 lightPosition = vec3(100.0, 100.0, 100.0);
    float dotProduct = dot(v_RotatedNormal.xyz,normalize(lightPosition - v_Position));
    float brightness = (dotProduct + 1) / 2; 

    FragColor = vec4((v_Color * brightness), 1.0);
}
