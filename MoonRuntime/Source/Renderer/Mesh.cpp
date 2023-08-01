#include "Mesh.hpp"

#include <glad/gl.h>

void Mesh::UseShader()
{
    m_Shader.Bind();
}

void Mesh::Draw()
{
    m_VertexBuffer.Bind();
    m_VertexBuffer.Draw();
    m_VertexBuffer.Unbind();
}
