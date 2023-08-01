#pragma once

#include <glm/glm.hpp>

// TODO Add Skybox
// TODO Add Light Direction Change

class Environment
{
public:
    Environment() = default;
    virtual ~Environment() = default;

    virtual void Update(float dt) {}

protected:
    glm::vec3 m_LightPosition = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_LightDirection = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_Gravity = { 0.0f, 0.0f, 0.0f };

public:
    glm::vec3 GetLightDirection() const { return m_LightDirection; }
    void SetLightDirection(const glm::vec3& lightDirection) { m_LightDirection = lightDirection; }

    glm::vec3 GetGravity() const { return m_Gravity; }
    void SetGravity(const glm::vec3& gravity) { m_Gravity = gravity; }

    glm::vec3 GetLightPosition() const { return m_LightPosition; }
    void SetLightPosition(const glm::vec3 &lightPosition) { m_LightPosition = lightPosition; }
};