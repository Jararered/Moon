#pragma once

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

class CircleCollider
{
public:
    CircleCollider() = default;
    virtual ~CircleCollider() = default;

    CircleCollider(float radius) : m_Radius(radius) {}

private:
    float m_Radius;

public:
    float GetRadius() const { return m_Radius; }
    void SetRadius(float radius) { m_Radius = radius; }
};
