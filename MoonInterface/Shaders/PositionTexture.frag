#version 330 core
out vec4 FragColor;

in vec2 v_TexureCoordinates;

uniform sampler2D u_Texture;

void main()
{
    vec3 textureColor = texture(u_Texture, v_TexureCoordinates).rgb;
    FragColor = vec4(textureColor, 1.0);
}