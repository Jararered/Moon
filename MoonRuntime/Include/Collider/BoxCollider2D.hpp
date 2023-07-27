#pragma once

#include "Collider.hpp"

#include <glm/vec3.hpp>

class BoxCollider2D : public Collider
{
public:
    BoxCollider2D() = default;
    ~BoxCollider2D() override = default;

    BoxCollider2D(glm::vec3 position, float scale);

private:
    glm::vec3 m_Position;
    float m_Scale;
};