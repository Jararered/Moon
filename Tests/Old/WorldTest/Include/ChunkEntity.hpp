#pragma once

#include <Entity.hpp>

#include "ChunkData.hpp"
#include "ChunkManager.hpp"
#include "ChunkMesh.hpp"

#include <array>

class ChunkEntity : public Entity
{
public:
    ChunkEntity() = default;
    ~ChunkEntity() = default;

    static ChunkManager s_ChunkManager;

    void Update(float dt) override
    {
        // float distance = (glm::sin(Engine::GetTime()) + 1.0f) / 2.0f;
        // glm::vec3 newPosition = m_Position;
        auto& matrix = p_Mesh->GetTranslationMatrix();
        matrix = glm::translate(matrix, m_Position);

        auto& rotation = GetMesh()->GetRotationMatrix();
        // rotation = glm::rotate(rotation, glm::radians(dt * m_Position.x), glm::vec3(1.0f, 0.0f, 0.0f));
        rotation = glm::rotate(rotation, glm::radians(dt * m_Position.y), glm::vec3(0.0f, m_Position.y, 0.0f));
        // rotation = glm::rotate(rotation, glm::radians(dt * m_Position.z), glm::vec3(0.0f, 0.0f, 1.0f));
    }

private:
    ChunkData m_ChunkData;
};