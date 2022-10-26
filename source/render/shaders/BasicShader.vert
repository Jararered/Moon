#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Color;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;

out vec4 v_Color;

void main()
{
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * vec4(a_Position, 1.0);
    v_Color = vec4(a_Color, 1.0);
}
