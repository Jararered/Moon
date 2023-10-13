#pragma once

#include <Components/Mesh.hpp>

class Voxel : public MeshTemplate<Vertex1D<glm::vec3>> // Position, Normal, Texture Coordinate
{
public:
    Voxel(glm::vec3 position = glm::vec3(0.0f))
    {
        using Vertex = Vertex1D<glm::vec3>;

        auto& vertices = VertexBuffer.GetVertices();
        vertices.reserve(1);
        vertices.emplace_back(Vertex({position.x, position.y, position.z}));

        auto& indices = VertexBuffer.GetIndices();
        indices.reserve(1);
        indices.insert(indices.end(), {0});

        VertexBuffer.BufferData();
    }
};