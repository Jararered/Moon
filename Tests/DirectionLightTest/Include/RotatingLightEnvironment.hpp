#pragma once

#include "Environment.hpp"

#include <glm/gtx/rotate_vector.hpp>

class RotatingLightEnvironment : public Environment
{
public:
    RotatingLightEnvironment()
    {
        m_LightDirection = glm::vec3(1.0f, -1.0f, 0.0f);

    }

    void Update(float dt) override
    {
        m_LightDirection = glm::rotateY(m_LightDirection, dt);
    }
};