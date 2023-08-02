#pragma once

#include <Mesh.hpp>

class SquareMesh : public MeshTemplate<Vertex3D<glm::vec3, glm::vec3, glm::vec3>>
{
public:
    SquareMesh(float size = 1.0f, const glm::vec3& color = { 1.0f, 0.0f, 0.0f })
    {
        m_VertexBuffer.GetIndices().insert(m_VertexBuffer.GetIndices().end(), { 0, 1, 2, 2, 3, 0 });
        m_VertexBuffer.GetVertices().emplace_back(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{ +size / 2.0f, -size / 2.0f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f }));
        m_VertexBuffer.GetVertices().emplace_back(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{ +size / 2.0f, +size / 2.0f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f }));
        m_VertexBuffer.GetVertices().emplace_back(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{ -size / 2.0f, +size / 2.0f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f }));
        m_VertexBuffer.GetVertices().emplace_back(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{ -size / 2.0f, -size / 2.0f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f }));

        m_VertexBuffer.Generate();
    }
};