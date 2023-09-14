#version 330 core

in vec2 v_TextureCoordinate;

out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TextureCoordinate);
    if (texColor.a < 0.1)
        discard;
    FragColor = vec4(texColor, 1.0);
}
