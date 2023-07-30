#pragma once

#include <Entity.hpp>

#include "CubeMesh.hpp"

class CubeEntity : public Entity
{
public:
    CubeEntity(glm::vec3 position = { 0.0f, 0.0f, 0.0f }, float scale = 1.0f)
    {
        m_Position = position;

        glm::vec3 white = glm::vec3(1.0f);
        p_Mesh = new CubeMesh(white);

        auto& translation = GetMesh()->GetTranslationMatrix();
        translation = glm::translate(translation, m_Position);
        translation = glm::scale(translation, glm::vec3(scale));
    }

    void Update(float dt) override
    {
        auto& rotation = GetMesh()->GetRotationMatrix();
        rotation = glm::rotate(rotation, glm::radians(0.25f * dt * m_Position.x), glm::vec3(1.0f, 0.0f, 0.0f));
        rotation = glm::rotate(rotation, glm::radians(0.25f * dt * m_Position.y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotation = glm::rotate(rotation, glm::radians(0.25f * dt * m_Position.z), glm::vec3(0.0f, 0.0f, 1.0f));
    }
};