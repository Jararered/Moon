#version 330 core

in vec3 v_Color;
in vec2 v_TextureCoordinate;

out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, v_TextureCoordinate) * vec4(v_Color, 1.0);
    if (texColor.a < 0.1)
        discard;
    // FragColor = texColor;
    FragColor = vec4(v_Color, 1.0);
}
