#version 330 core

in vec4 v_RotatedNormal;

out vec4 FragColor;

void main()
{
    vec3 lightDirection = vec3(1.0, -1.0, 1.0);

    // 0 to 1
    float lightBrightness = (dot(v_RotatedNormal.xyz, lightDirection) + 1) / 2; 
    // 0.5 to 1
    lightBrightness = (lightBrightness + 1.0) / 2; 
    
    FragColor = vec4((vec3(1.0, 1.0, 1.0) * lightBrightness), 1.0);
}
