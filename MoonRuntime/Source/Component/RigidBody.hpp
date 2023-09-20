#pragma once

#include <glm/vec3.hpp>

struct RigidBody
{
    glm::vec3 Velocity = glm::vec3(0.0f);
    glm::vec3 Acceleration = glm::vec3(0.0f);
    float Mass = 0;
};