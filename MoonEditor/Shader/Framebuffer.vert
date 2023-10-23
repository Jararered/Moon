#version 330 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TextureCoordinate;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

out vec2 v_TextureCoordinate;

void main()
{
    v_TextureCoordinate = a_TextureCoordinate;

    gl_Position = vec4(a_Position, 0.0, 1.0);
}