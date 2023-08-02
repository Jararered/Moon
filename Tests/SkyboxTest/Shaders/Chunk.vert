#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;

uniform mat4 u_TranslationMatrix;
uniform mat4 u_RotationMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

out vec4 v_RotatedNormal;

void main()
{
    v_RotatedNormal = u_RotationMatrix * vec4(a_Normal, 1.0);

    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_TranslationMatrix * u_RotationMatrix * vec4(a_Position, 1.0);
}
