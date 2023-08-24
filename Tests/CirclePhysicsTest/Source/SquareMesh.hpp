#pragma once

#include <Mesh.hpp>

class SquareMesh : public TMeshComponent<Vertex3D<glm::vec3, glm::vec3, glm::vec2>> // Position, Color, Texture
{
public:
    SquareMesh(const glm::vec3& color = glm::vec3(1.0f))
    {
        auto& vertices = VertexBuffer.GetVertices();
        auto& indices = VertexBuffer.GetIndices();

        indices.insert(VertexBuffer.GetIndices().end(), {0, 1, 2, 2, 3, 0});
        vertices.emplace_back(Vertex3D<glm::vec3, glm::vec3, glm::vec2>({+0.5f, -0.5f, 0.0f}, color, {1.0f, 0.0f}));
        vertices.emplace_back(Vertex3D<glm::vec3, glm::vec3, glm::vec2>({+0.5f, +0.5f, 0.0f}, color, {1.0f, 1.0f}));
        vertices.emplace_back(Vertex3D<glm::vec3, glm::vec3, glm::vec2>({-0.5f, +0.5f, 0.0f}, color, {0.0f, 1.0f}));
        vertices.emplace_back(Vertex3D<glm::vec3, glm::vec3, glm::vec2>({-0.5f, -0.5f, 0.0f}, color, {0.0f, 0.0f}));
        VertexBuffer.Create();
    }
};