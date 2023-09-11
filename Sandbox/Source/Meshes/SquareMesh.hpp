#pragma once

#include <Mesh.hpp>

class SquareMesh : public MeshTemplate<Vertex3D<glm::vec3, glm::vec3, glm::vec2>> // Position, Color, Texture
{
public:
    SquareMesh(const glm::vec3& color = glm::vec3(1.0f))
    {
        using Vertex = Vertex3D<glm::vec3, glm::vec3, glm::vec2>;

        auto& vertices = VertexBuffer.GetVertices();
        vertices.reserve(4);
        vertices.emplace_back(Vertex({+0.5f, -0.5f, 0.0f}, color, {1.0f, 0.0f}));
        vertices.emplace_back(Vertex({+0.5f, +0.5f, 0.0f}, color, {1.0f, 1.0f}));
        vertices.emplace_back(Vertex({-0.5f, +0.5f, 0.0f}, color, {0.0f, 1.0f}));
        vertices.emplace_back(Vertex({-0.5f, -0.5f, 0.0f}, color, {0.0f, 0.0f}));

        auto& indices = VertexBuffer.GetIndices();
        indices.reserve(6);
        indices.insert(VertexBuffer.GetIndices().end(), {0, 1, 2, 2, 3, 0});

        VertexBuffer.UploadToGPU();
    }
};