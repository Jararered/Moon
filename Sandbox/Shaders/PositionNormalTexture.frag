#version 330 core

in vec3 v_Position;
in vec2 v_TextureCoordinate;

out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
    float brightness = 0.0;

    vec4 texColor = texture(u_Texture, v_TextureCoordinate);
    if (texColor.a < 0.1)
        discard;
    if (texColor.r > 0.5)
        brightness = 1.0;

    FragColor = texColor * vec4(brightness, brightness, brightness, 1.0);
}
