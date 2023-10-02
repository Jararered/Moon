#pragma once

#include <glm/vec3.hpp>

enum Status
{
    None = 0,
    Grounded = 1,
    Falling = 2
};

struct RigidBody
{
    glm::vec3 Velocity = glm::vec3(0.0f);
    glm::vec3 Acceleration = glm::vec3(0.0f);
    float Mass = 0.0f;
    int MovementStatus = Status::None;
};