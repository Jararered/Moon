#pragma once

#include <Mesh.hpp>

class SkyboxMesh : public MeshTemplate<Vertex2D<glm::vec3, glm::vec2>>
{
public:
    SkyboxMesh()
    {
        auto& indices = m_VertexBuffer.GetIndices();
        auto& vertices = m_VertexBuffer.GetVertices();

        indices.insert(indices.end(), {
            0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 8, 9, 10, 10, 11, 8,
            12, 13, 14, 14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20
            });

        const float ONE_THIRDS = 0.33333333f;
        const float TWO_THIRDS = 0.66666666f;

        // Right +x
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+500.0f, +500.0f, -500.0f), glm::vec2(0.75f, TWO_THIRDS)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+500.0f, -500.0f, -500.0f), glm::vec2(0.75f, ONE_THIRDS)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+500.0f, -500.0f, +500.0f), glm::vec2(0.5f, ONE_THIRDS)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+500.0f, +500.0f, +500.0f), glm::vec2(0.5f, TWO_THIRDS)));

        // Left -x
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-500.0f, +500.0f, +500.0f), glm::vec2(0.25f, TWO_THIRDS)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-500.0f, -500.0f, +500.0f), glm::vec2(0.25f, ONE_THIRDS)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-500.0f, -500.0f, -500.0f), glm::vec2(0.0f, ONE_THIRDS)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-500.0f, +500.0f, -500.0f), glm::vec2(0.0f, TWO_THIRDS)));

        // Top +y
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+500.0f, +500.0f, +500.0f), glm::vec2(0.5f, TWO_THIRDS)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-500.0f, +500.0f, +500.0f), glm::vec2(0.25f, TWO_THIRDS)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-500.0f, +500.0f, -500.0f), glm::vec2(0.25f, 1.0f)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+500.0f, +500.0f, -500.0f), glm::vec2(0.5f, 1.0f)));

        // Bottom -y
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-500.0f, -500.0f, -500.0f), glm::vec2(0.25f, 0.0f)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-500.0f, -500.0f, +500.0f), glm::vec2(0.25f, ONE_THIRDS)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+500.0f, -500.0f, +500.0f), glm::vec2(0.5f, ONE_THIRDS)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+500.0f, -500.0f, -500.0f), glm::vec2(0.5f, 0.0f)));

        // Front +z
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-500.0f, +500.0f, +500.0), glm::vec2(0.25f, TWO_THIRDS)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+500.0f, +500.0f, +500.0), glm::vec2(0.5f, TWO_THIRDS)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+500.0f, -500.0f, +500.0), glm::vec2(0.5f, ONE_THIRDS)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-500.0f, -500.0f, +500.0), glm::vec2(0.25f, ONE_THIRDS)));

        // Back -z
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+500.0f, +500.0f, -500.0f), glm::vec2(0.75f, TWO_THIRDS)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-500.0f, +500.0f, -500.0f), glm::vec2(1.0f, TWO_THIRDS)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-500.0f, -500.0f, -500.0f), glm::vec2(1.0f, ONE_THIRDS)));
        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+500.0f, -500.0f, -500.0f), glm::vec2(0.75f, ONE_THIRDS)));

        m_VertexBuffer.Generate();
    }
};