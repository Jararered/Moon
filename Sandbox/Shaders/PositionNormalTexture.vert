#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TextureCoordinate;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

out vec3 v_Position;
out vec3 v_Normal;
out vec2 v_TextureCoordinate;

void main()
{
    v_Position = a_Position;
    v_Normal = a_Normal;
    v_TextureCoordinate = a_TextureCoordinate;

    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
}
