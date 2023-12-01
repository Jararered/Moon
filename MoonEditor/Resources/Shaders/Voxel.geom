#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 24) out;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main()
{
    mat4 ModelViewProjection = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix;
    vec4 position;

    position = gl_in[0].gl_Position + vec4(-0.5, -0.5, +0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(+0.5, -0.5, +0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(-0.5, +0.5, +0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(+0.5, +0.5, +0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    EndPrimitive();

    position = gl_in[0].gl_Position + vec4(+0.5, -0.5, -0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(-0.5, -0.5, -0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(+0.5, +0.5, -0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(-0.5, +0.5, -0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    EndPrimitive();

    position = gl_in[0].gl_Position + vec4(+0.5, +0.5, +0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(+0.5, -0.5, +0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(+0.5, +0.5, -0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(+0.5, -0.5, -0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    EndPrimitive();

    position = gl_in[0].gl_Position + vec4(-0.5, +0.5, -0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(-0.5, -0.5, -0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(-0.5, +0.5, +0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(-0.5, -0.5, +0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    EndPrimitive();

    position = gl_in[0].gl_Position + vec4(+0.5, +0.5, -0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(-0.5, +0.5, -0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(+0.5, +0.5, +0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(-0.5, +0.5, +0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    EndPrimitive();

    position = gl_in[0].gl_Position + vec4(-0.5, -0.5, -0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(+0.5, -0.5, -0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(-0.5, -0.5, +0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    position = gl_in[0].gl_Position + vec4(+0.5, -0.5, +0.5, 0.0);
    gl_Position = ModelViewProjection * position;
    EmitVertex();
    EndPrimitive();
}
