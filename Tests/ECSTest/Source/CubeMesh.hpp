#pragma once

#include <Components/Mesh.hpp>

class CubeMesh : public TMeshComponent<Vertex2D<glm::vec3, glm::vec3>> // Position, Color
{
public:
    CubeMesh(const glm::vec3& color)
    {
        auto& vertices = VertexBuffer.GetVertices();
        auto& indices = VertexBuffer.GetIndices();

        indices.insert(indices.end(), {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14, 14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20});

        // Front
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{-0.5f, -0.5f, 0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{+0.5f, -0.5f, 0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{+0.5f, +0.5f, 0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{-0.5f, +0.5f, 0.5f}, color));

        // Back
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{+0.5f, -0.5f, -0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{-0.5f, -0.5f, -0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{-0.5f, +0.5f, -0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{+0.5f, +0.5f, -0.5f}, color));

        // Right
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{+0.5f, +0.5f, +0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{+0.5f, -0.5f, +0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{+0.5f, -0.5f, -0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{+0.5f, +0.5f, -0.5f}, color));

        // Left
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{-0.5f, +0.5f, -0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{-0.5f, -0.5f, -0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{-0.5f, -0.5f, +0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{-0.5f, +0.5f, +0.5f}, color));

        // Top
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{+0.5f, +0.5f, -0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{-0.5f, +0.5f, -0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{-0.5f, +0.5f, +0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{+0.5f, +0.5f, +0.5f}, color));

        // Bottom
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{+0.5f, -0.5f, -0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{+0.5f, -0.5f, +0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{-0.5f, -0.5f, +0.5f}, color));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>(glm::vec3{-0.5f, -0.5f, -0.5f}, color));

        VertexBuffer.Generate();
    }
};