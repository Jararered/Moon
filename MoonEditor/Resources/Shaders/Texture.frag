#version 330 core

in vec2 v_TextureCoordinate;

uniform sampler2D u_Texture;

out vec4 FragColor;

void main()
{
    FragColor = texture(u_Texture, v_TextureCoordinate);
}
