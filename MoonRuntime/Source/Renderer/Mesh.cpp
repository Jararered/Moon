#include "Mesh.hpp"

#include <glad/gl.h>

void Mesh::Bind()
{
    m_Shader.Bind();
    m_Texture.Bind();
    m_VertexBuffer.Bind();
}

void Mesh::Unbind()
{
    m_Shader.Unbind();
    m_Texture.Unbind();
    m_VertexBuffer.Unbind();
}

void Mesh::Draw()
{
    Bind();
    m_VertexBuffer.Draw();
    Unbind();
}
