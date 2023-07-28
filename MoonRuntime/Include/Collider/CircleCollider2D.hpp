#pragma once

#include "Collider.hpp"

#include <glm/vec4.hpp>

class CircleCollider2D : public Collider
{
public:
    CircleCollider2D() = default;
    virtual ~CircleCollider2D() override = default;
    CircleCollider2D(const glm::vec3& position, float radius)
        :m_Position(position), m_Radius(radius)
    {
    }

private:
    glm::vec3 m_Position;
    float m_Radius;

public:
    glm::vec3 GetPosition() const { return m_Position; }
    void SetPosition(const glm::vec3& position) { m_Position = position; }

    float GetRadius() const { return m_Radius; }
    void SetRadius(float radius) { m_Radius = radius; }
};