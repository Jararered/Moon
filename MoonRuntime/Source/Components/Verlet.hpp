#pragma once

#include <glm/vec3.hpp>

struct Verlet
{
    glm::vec3 LastPosition = {0.0f, 0.0f, 0.0f};
    float Radius = 0.0f;
};