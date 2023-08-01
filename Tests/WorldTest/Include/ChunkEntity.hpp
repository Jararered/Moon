#pragma once

#include <Entity.hpp>

#include "ChunkMesh.hpp"
#include "ChunkData.hpp"
#include "ChunkManager.hpp"

#include <array>

class ChunkEntity : public Entity
{
public:
    ChunkEntity() = default;
    ~ChunkEntity() = default;

    static ChunkManager s_ChunkManager;

    void Update(float dt) override
    {
        float distance = (glm::sin(glfwGetTime()) + 1.0f) / 2.0f;
        glm::vec3 newPosition = m_Position;

        glm::mat4 matrix = glm::translate(glm::mat4(1.0f), m_Position);
        p_Mesh->SetTranslationMatrix(matrix);
    }

private:
    ChunkData m_ChunkData;
};