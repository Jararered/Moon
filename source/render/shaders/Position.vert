#version 330 core

layout (location = 0) in vec3 a_Position;

uniform float u_Time;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;

void main()
{
    mat4 mvp = u_ProjectionMatrix * u_ViewMatrix * mat4(1.0);
    gl_Position = mvp * vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
}
