#pragma once

#include <Mesh.hpp>

class SquareMesh : public MeshTemplate<Vertex3V3>
{
public:
    SquareMesh(const glm::vec3& color = { 1.0f, 0.0f, 0.0f })
    {
        m_VertexBuffer.GetIndices().insert(m_VertexBuffer.GetIndices().end(), { 0, 1, 2, 2, 3, 0 });
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, -0.5f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f }));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, +0.5f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f }));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, +0.5f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f }));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, -0.5f, 0.0f }, color, glm::vec3{ 0.0f, 0.0f, 1.0f }));

        m_VertexBuffer.Generate();
    }
};