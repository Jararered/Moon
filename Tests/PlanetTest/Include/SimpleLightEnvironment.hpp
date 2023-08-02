#pragma once

#include "Environment.hpp"

#include <glm/trigonometric.hpp>

class SimpleLightEnvironment : public Environment
{
public:
    SimpleLightEnvironment()
    {
        m_LightDirection = glm::normalize(glm::vec3(0.8f, 1.0f, 0.0f));
    }
};