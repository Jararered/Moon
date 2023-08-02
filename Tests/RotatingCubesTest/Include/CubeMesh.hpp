#pragma once

#include <Mesh.hpp>

class CubeMesh : public MeshTemplate<Vertex3V3>
{
public:
    CubeMesh(const glm::vec3& color = { 1.0f, 0.0f, 0.0f })
    {
        auto& vertices = m_VertexBuffer.GetVertices();
        auto& indices = m_VertexBuffer.GetIndices();

        indices.insert(indices.end(), {
            0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4,
            8, 9, 10, 10, 11, 8, 12, 13, 14, 14, 15, 12,
            16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20
            });

        // Front
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, -0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, -0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, +0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, +0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f)));

        // Back
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f)));

        // Right
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, +0.5f, +0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, -0.5f, +0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, -0.5f, -0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, +0.5f, -0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f)));

        // Left
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, +0.5f, -0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, -0.5f, -0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, -0.5f, +0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, +0.5f, +0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f)));

        // Top
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, +0.5f, +0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, +0.5f, +0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f)));

        // Bottom
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, -0.5f, +0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, -0.5f, +0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f)));

        m_VertexBuffer.Generate();
    }
};