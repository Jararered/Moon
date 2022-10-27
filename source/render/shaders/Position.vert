#version 330 core

layout (location = 0) in vec3 a_Position;

uniform float u_Time;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;

void main()
{
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * vec4(a_Position, 1.0);
}
