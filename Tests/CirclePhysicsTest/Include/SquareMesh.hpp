#pragma once

#include <Mesh.hpp>

class SquareMesh : public Mesh<Vertex2D<glm::vec3, glm::vec2>>
{
public:
    SquareMesh(float size = 1.0f)
    {
        m_VertexBuffer.GetIndices().insert(m_VertexBuffer.GetIndices().end(), {0, 1, 2, 2, 3, 0});
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>({+size / 2.0f, -size / 2.0f, 0.0f}, {1.0f, 0.0f}));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>({+size / 2.0f, +size / 2.0f, 0.0f}, {1.0f, 1.0f}));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>({-size / 2.0f, +size / 2.0f, 0.0f}, {0.0f, 1.0f}));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>({-size / 2.0f, -size / 2.0f, 0.0f}, {0.0f, 0.0f}));

        m_VertexBuffer.Generate();
    }
};