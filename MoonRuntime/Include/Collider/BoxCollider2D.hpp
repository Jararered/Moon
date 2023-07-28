#pragma once

#include "Collider.hpp"

#include <glm/vec4.hpp>

class BoxCollider2D : public Collider
{
public:
    BoxCollider2D() = default;
    ~BoxCollider2D() override = default;

    BoxCollider2D(float positivex, float negativex, float positivey, float negativey)
        :m_PositiveX(positivex), m_NegativeX(negativex), m_PositiveY(positivey), m_NegativeY(negativey)
    {
    }

    float PositiveX() const { return m_PositiveX; }
    void SetPositiveX(float PositiveX) { m_PositiveX = PositiveX; }

    float NegativeX() const { return m_NegativeX; }
    void SetNegativeX(float NegativeX) { m_NegativeX = NegativeX; }

    float PositiveY() const { return m_PositiveY; }
    void SetPositiveY(float PositiveY) { m_PositiveY = PositiveY; }

    float NegativeY() const { return m_NegativeY; }
    void SetNegativeY(float NegativeY) { m_NegativeY = NegativeY; }

private:
    float m_PositiveX;
    float m_NegativeX;
    float m_PositiveY;
    float m_NegativeY;
};