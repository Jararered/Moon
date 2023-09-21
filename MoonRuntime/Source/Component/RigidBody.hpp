#pragma once

#include <glm/vec3.hpp>

struct RigidBody
{
    glm::vec3 Velocity = {0.0f, 0.0f, 0.0f};
    glm::vec3 Acceleration = {0.0f, 0.0f, 0.0f};
    float Mass = 0.0f;
    float Compressability = 0.0f;
};