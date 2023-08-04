#pragma once

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

class CircleCollider
{
public:
    CircleCollider() = default;
    virtual ~CircleCollider() = default;

    CircleCollider(const glm::vec3& position, float radius) : m_Position(position), m_Radius(radius) {}

    bool IsIntersect(const CircleCollider* collider)
    {
        float distance = glm::distance(this->GetPosition(), collider->GetPosition());
        if (distance > this->GetRadius() / 2.0f + collider->GetRadius() / 2.0f)
            return false;

        return true;
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
