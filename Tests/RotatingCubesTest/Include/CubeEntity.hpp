#pragma once

#include <Entity.hpp>

#include "CubeMesh.hpp"

class CubeEntity : public Entity
{
public:
    CubeEntity(glm::vec3 position = { 0.0f, 0.0f, 0.0f }, float scale = 1.0f)
    {
        m_Position = position;

        constexpr glm::vec3 white = { 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f };

        p_Mesh = new CubeMesh(white);

        auto& translation = p_Mesh->GetTranslationMatrix();
        translation = glm::translate(translation, position);
        translation = glm::scale(translation, { scale, scale, scale });
    }

    void Update(float dt) override
    {
        auto& rotation = p_Mesh->GetRotationMatrix();
        rotation = glm::rotate(rotation, glm::radians(m_Position.x * dt), glm::vec3(1.0f, 0.0f, 0.0f));
        rotation = glm::rotate(rotation, glm::radians(m_Position.y * dt), glm::vec3(0.0f, 1.0f, 0.0f));
        rotation = glm::rotate(rotation, glm::radians(m_Position.z * dt), glm::vec3(0.0f, 0.0f, 1.0f));
    }
};