#pragma once

#include <Components/Mesh.hpp>

class TexturedCubeMesh : public MeshTemplate<Vertex3D<glm::vec3, glm::vec3, glm::vec2>> // Position, Normal, Texture Coordinate
{
public:
    TexturedCubeMesh()
    {
        using Vertex = Vertex3D<glm::vec3, glm::vec3, glm::vec2>;

        auto& vertices = VertexBuffer.GetVertices();
        vertices.reserve(24);

        vertices.emplace_back(Vertex({-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}));
        vertices.emplace_back(Vertex({+0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}));
        vertices.emplace_back(Vertex({+0.5f, +0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}));
        vertices.emplace_back(Vertex({-0.5f, +0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}));

        vertices.emplace_back(Vertex({+0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}));
        vertices.emplace_back(Vertex({-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}));
        vertices.emplace_back(Vertex({-0.5f, +0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}));
        vertices.emplace_back(Vertex({+0.5f, +0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}));

        vertices.emplace_back(Vertex({+0.5f, +0.5f, +0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}));
        vertices.emplace_back(Vertex({+0.5f, -0.5f, +0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}));
        vertices.emplace_back(Vertex({+0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}));
        vertices.emplace_back(Vertex({+0.5f, +0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}));

        vertices.emplace_back(Vertex({-0.5f, +0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}));
        vertices.emplace_back(Vertex({-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}));
        vertices.emplace_back(Vertex({-0.5f, -0.5f, +0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}));
        vertices.emplace_back(Vertex({-0.5f, +0.5f, +0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}));

        vertices.emplace_back(Vertex({+0.5f, +0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}));
        vertices.emplace_back(Vertex({-0.5f, +0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}));
        vertices.emplace_back(Vertex({-0.5f, +0.5f, +0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}));
        vertices.emplace_back(Vertex({+0.5f, +0.5f, +0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}));

        vertices.emplace_back(Vertex({-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}));
        vertices.emplace_back(Vertex({+0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}));
        vertices.emplace_back(Vertex({+0.5f, -0.5f, +0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}));
        vertices.emplace_back(Vertex({-0.5f, -0.5f, +0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}));

        auto& indices = VertexBuffer.GetIndices();
        indices.reserve(36);
        indices.insert(indices.end(), {0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 8, 9, 10, 10, 11, 8, 12, 13, 14, 14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20});

        VertexBuffer.UploadToGPU();
    }
};