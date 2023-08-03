#pragma once

#include "Entity.hpp"
#include "Mesh.hpp"

class SkyboxMesh : public Mesh<Vertex2D<glm::vec3, glm::vec2>>
{
public:
    SkyboxMesh()
    {
        m_VertexBuffer.GetIndices().insert(m_VertexBuffer.GetIndices().end(), {
            0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4, 8, 9, 10, 10, 11, 8,
            12, 13, 14, 14, 15, 12, 16, 17, 18, 18, 19, 16, 20, 21, 22, 22, 23, 20
            });

        // Right +x
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+1.0f, +1.0f, -1.0f), glm::vec2(0.75f, 0.66666666f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec2(0.75f, 0.33333333f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec2(0.5f, 0.33333333f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+1.0f, +1.0f, +1.0f), glm::vec2(0.5f, 0.66666666f)));

        // Left -x
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-1.0f, +1.0f, +1.0f), glm::vec2(0.25f, 0.66666666f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec2(0.25f, 0.33333333f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.33333333f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-1.0f, +1.0f, -1.0f), glm::vec2(0.0f, 0.66666666f)));

        // Top +y
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+1.0f, +1.0f, +1.0f), glm::vec2(0.5f, 0.66666666f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-1.0f, +1.0f, +1.0f), glm::vec2(0.25f, 0.66666666f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-1.0f, +1.0f, -1.0f), glm::vec2(0.25f, 1.0f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+1.0f, +1.0f, -1.0f), glm::vec2(0.5f, 1.0f)));

        // Bottom -y
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.25f, 0.0f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-1.0f, -1.0f, +1.0f), glm::vec2(0.25f, 0.33333333f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+1.0f, -1.0f, +1.0f), glm::vec2(0.5f, 0.33333333f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec2(0.5f, 0.0f)));

        // Front +z
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-1.0f, +1.0f, +1.0), glm::vec2(0.25f, 0.66666666f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+1.0f, +1.0f, +1.0), glm::vec2(0.5f, 0.66666666f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+1.0f, -1.0f, +1.0), glm::vec2(0.5f, 0.33333333f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-1.0f, -1.0f, +1.0), glm::vec2(0.25f, 0.33333333f)));

        // Back -z
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+1.0f, +1.0f, -1.0f), glm::vec2(0.75f, 0.66666666f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-1.0f, +1.0f, -1.0f), glm::vec2(1.0f, 0.66666666f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.33333333f)));
        AddToVertexBuffer(Vertex2D<glm::vec3, glm::vec2>(glm::vec3(+1.0f, -1.0f, -1.0f), glm::vec2(0.75f, 0.33333333f)));

        m_VertexBuffer.Generate();
    }
};

class SkyboxEntity : public Entity
{
public:
    SkyboxEntity() = default;
    virtual ~SkyboxEntity() = default;

    void Update(float dt) override
    {
        auto matrix = glm::mat4(1.0f);
        matrix = glm::translate(matrix, *p_PositionReference);
        p_Mesh->SetTranslationMatrix(matrix);
    }

    void SetPositionReference(glm::vec3* position)
    {
        p_PositionReference = position;
    }

private:
    glm::vec3* p_PositionReference = nullptr;
};