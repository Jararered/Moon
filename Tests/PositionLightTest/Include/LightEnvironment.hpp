#pragma once

#include "Environment.hpp"

#include <glm/gtx/rotate_vector.hpp>

class LightEnvironment : public Environment
{
public:
    LightEnvironment()
    {
    }

    void Update(float dt) override
    {
        float distance = 50.0f;
        m_LightPosition = glm::vec3(glm::sin(dt) * distance, 50.0f, 0.0f);
    }
};