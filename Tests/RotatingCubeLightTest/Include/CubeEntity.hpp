#pragma once

#include <DynamicEntity.hpp>

#include "CubeMesh.hpp"

class CubeEntity : public DynamicEntity
{
public:
    CubeEntity(glm::vec3 position = { 0.0f, 0.0f, 0.0f }, float scale = 1.0f)
    {
        m_Position = position;
        m_Scale = scale;

        glm::vec3 white = glm::vec3(1.0f);
        p_Mesh = new CubeMesh(white);

        glm::mat4 matrix = p_Mesh->GetTranslationMatrix();
        matrix = glm::translate(matrix, m_Position);
        matrix = glm::scale(matrix, { m_Scale, m_Scale, m_Scale });
        p_Mesh->SetTranslationMatrix(matrix);
    }

    void Update(float dt) override
    {
        // Rotate
        glm::mat4 rotation = p_Mesh->GetRotationMatrix();
        rotation = glm::rotate(rotation, glm::radians(0.25f * dt * m_Position.x), glm::vec3(1.0f, 0.0f, 0.0f));
        // rotation = glm::rotate(rotation, glm::radians(0.25f * dt * m_Position.y), glm::vec3(0.0f, 1.0f, 0.0f));
        // rotation = glm::rotate(rotation, glm::radians(0.25f * dt * m_Position.z), glm::vec3(0.0f, 0.0f, 1.0f));
        
        p_Mesh->SetRotationMatrix(rotation);

        // glm::mat4 translation = p_Mesh->GetTranslationMatrix();
        // float sinValue = glm::sin(3.0f * static_cast<float>(glfwGetTime()));
        // glm::vec3 normalized = glm::normalize(m_Position) * 0.1f * sinValue;
        // translation = glm::translate(translation, normalized);
        // translation = glm::scale(translation, { 2.0f * sinValue * dt + 1.0f,  2.0f * sinValue * dt + 1.0f,  2.0f * sinValue * dt + 1.0f });
        // p_Mesh->SetTranslationMatrix(translation);
    }
};