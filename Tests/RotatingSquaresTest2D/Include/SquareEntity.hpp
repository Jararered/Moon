#pragma once

#include <Entity.hpp>

#include "SquareMesh.hpp"

class SquareEntity : public Entity
{
public:
    SquareEntity(glm::vec3 position = { 0.0f, 0.0f, 0.0f }, float scale = 1.0f)
    {
        m_Position = position;

        glm::vec3 green = { 129.0f / 255.0f, 192.0f / 255.0f, 70.0f / 255.0f };
        glm::vec3 red = { 222.0f / 255.0f, 72.0f / 255.0f, 43.0f / 255.0f };
        glm::vec3 blue = { 59.0f / 255.0f, 119.0f / 255.0f, 188.0f / 255.0f };
        glm::vec3 yellow = { 252.0f / 255.0f, 207.0f / 255.0f, 3.0f / 255.0f };

        if (position.x >= 0.0f && position.y >= 0.0f)
            p_Mesh = new SquareMesh(green);
        else if (position.x < 0.0f && position.y >= 0.0f)
            p_Mesh = new SquareMesh(red);
        else if (position.x < 0.0f && position.y < 0.0f)
            p_Mesh = new SquareMesh(blue);
        else
            p_Mesh = new SquareMesh(yellow);

        glm::mat4 matrix = p_Mesh->GetTranslationMatrix();
        matrix = glm::translate(matrix, position);
        matrix = glm::scale(matrix, { scale, scale, scale });
        p_Mesh->SetTranslationMatrix(matrix);
    }

    void Update(float dt) override
    {
        glm::mat4 rotation = p_Mesh->GetRotationMatrix();
        rotation = glm::rotate(rotation, glm::radians(dt * 1.0f * m_Position.x), glm::vec3(1.0f, 0.0f, 0.0f));
        // rotation = glm::rotate(rotation, glm::radians(dt * 2.0f * m_Position.x), glm::vec3(0.0f, 1.0f, 0.0f));
        // rotation = glm::rotate(rotation, glm::radians(dt * 3.0f * m_Position.x), glm::vec3(0.0f, 0.0f, 1.0f));
        p_Mesh->SetRotationMatrix(rotation);
    }
};