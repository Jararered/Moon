#pragma once

#include "Entity.hpp"

class DynamicEntity : public Entity
{
public:
    DynamicEntity() = default;

    virtual void Initialize(float dt) override {}
    virtual void Update(float dt) override {}
    virtual void Finalize(float dt) override {}

protected:
    glm::vec3 m_Velocity = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_Acceleration = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_GravitationalAcceleration = { 0.0f, 0.0f, 0.0f };

    float m_Yaw = 0.0f;
    float m_Pitch = 0.0f;
    float m_Roll = 0.0f;
};