#pragma once

#include <Mesh.hpp>

class CubeMesh : public Mesh
{
public:
    CubeMesh(const glm::vec3& color = { 1.0f, 0.0f, 0.0f })
    {
        std::vector<Vertex>& vertices = m_VertexBuffer.GetVertices();
        std::vector<unsigned int>& indices = m_VertexBuffer.GetIndices();

        indices.insert(indices.end(), {
            0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4,
            8, 9, 10, 10, 11, 8, 12, 13, 14, 14, 15, 12,
            16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20
            });

        // Front
        vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f));
        vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f));
        vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f));
        vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f));

        // Back
        vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f));
        vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f));
        vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f));
        vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f));

        // Right
        vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, +0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f));
        vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, +0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f));
        vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, -0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f));
        vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, -0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f));

        // Left
        vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, -0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f));
        vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, -0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f));
        vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, +0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f));
        vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, +0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f));

        // Top
        vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f));
        vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, -0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f));
        vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, +0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f));
        vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, +0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f));

        // Bottom
        vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f));
        vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, +0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f));
        vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, +0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f));
        vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, -0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f));

        m_VertexBuffer.Generate();
    }
};