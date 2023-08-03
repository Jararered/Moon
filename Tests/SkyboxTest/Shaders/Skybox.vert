#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureCoordinate;

uniform mat4 u_TranslationMatrix;
uniform mat4 u_RotationMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

out vec2 v_TextureCoordinate;

void main()
{
    v_TextureCoordinate = a_TextureCoordinate;

    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_TranslationMatrix * u_RotationMatrix * vec4(a_Position * 500.0, 1.0);
}
