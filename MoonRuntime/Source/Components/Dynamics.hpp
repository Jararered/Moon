#pragma once

#include <glm/vec3.hpp>

struct Dynamics
{
    glm::vec3 Velocity = glm::vec3(0.0f);
    glm::vec3 Acceleration = glm::vec3(0.0f);
};