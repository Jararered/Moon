#version 330 core

in vec4 v_RotatedNormal;

uniform vec3 u_LightDirection;

out vec4 FragColor;

void main()
{
    // 0 to 1
    float lightBrightness = (dot(v_RotatedNormal.xyz, u_LightDirection) + 1) / 2; 
    // 0.5 to 1
    lightBrightness = (lightBrightness + 1.0) / 2; 
    
    FragColor = vec4((vec3(1.0, 1.0, 1.0) * lightBrightness), 1.0);
}
