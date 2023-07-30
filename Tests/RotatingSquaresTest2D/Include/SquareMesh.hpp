#pragma once

#include <Mesh.hpp>

class SquareMesh : public Mesh
{
public:
    SquareMesh(const glm::vec3& color = { 1.0f, 0.0f, 0.0f })
    {
        m_VertexBuffer.GetIndices().insert(m_VertexBuffer.GetIndices().end(), { 0, 1, 2, 2, 3, 0 });
        m_VertexBuffer.GetVertices().emplace_back(glm::vec3{ +0.5f, -0.5f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f });
        m_VertexBuffer.GetVertices().emplace_back(glm::vec3{ +0.5f, +0.5f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f });
        m_VertexBuffer.GetVertices().emplace_back(glm::vec3{ -0.5f, +0.5f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f });
        m_VertexBuffer.GetVertices().emplace_back(glm::vec3{ -0.5f, -0.5f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f });

        m_VertexBuffer.Generate();
    }
};