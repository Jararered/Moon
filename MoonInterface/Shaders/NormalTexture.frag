#version 330 core

in vec3 v_Normal;
in vec2 v_TextureCoordinate;

out vec4 FragColor;

uniform sampler2D u_Texture;

void main()
{
    // Light
    vec3 lightDirection = vec3(0.333, -1.0, 0.666);
    float light = (dot(-1.0 * lightDirection, v_Normal) + 1.0) / 2.0;
    light = (light + 1.0) / 2.0;

    // Texture
    vec4 textureColor = texture(u_Texture, v_TextureCoordinate);
    if (textureColor.a < 0.1)
        discard;

    FragColor = textureColor * vec4(light, light, light, 1.0);
}
