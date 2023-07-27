#pragma once

#include <glm/vec3.hpp>

// TODO Add Skybox
// TODO Add Light Direction Change

class Environment
{
public:
    Environment() = default;
    virtual ~Environment() = default;

    virtual void Update(float dt) {}

    glm::vec3 GetLightDirection() { return m_LightDirection; }

protected:
    glm::vec3 m_LightDirection = { 0.0f, 0.0f, 0.0f };
};