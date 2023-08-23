#pragma once

#include <glm/vec3.hpp>

struct Dynamics
{
    glm::vec3 Velocity = {0.0f, 0.0f, 0.0f};
    glm::vec3 Acceleration = {0.0f, 0.0f, 0.0f};
};