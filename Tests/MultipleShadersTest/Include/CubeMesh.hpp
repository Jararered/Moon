#pragma once

#include <Mesh.hpp>

class CubeMesh : public Mesh<Vertex3V3>
{
public:
    CubeMesh(const glm::vec3& color = { 1.0f, 0.0f, 0.0f })
    {
        m_VertexBuffer.GetIndices().insert(m_VertexBuffer.GetIndices().end(), {
            0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 8, 9, 10, 10, 11, 8,
            12, 13, 14, 14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20
            });

        // Right +x
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, +0.5f, +0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, -0.5f, +0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, -0.5f, -0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, +0.5f, -0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f)));

        // Left -x
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, +0.5f, -0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, -0.5f, -0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, -0.5f, +0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, +0.5f, +0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f)));

        // Top +y
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, +0.5f, +0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, +0.5f, +0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f)));

        // Bottom -y
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, -0.5f, +0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, -0.5f, +0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f)));

        // Front +z
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, -0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, -0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, +0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, +0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f)));

        // Back -z
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ -0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f)));
        AddToVertexBuffer(Vertex3V3(glm::vec3{ +0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f)));

        m_VertexBuffer.Generate();
    }
};