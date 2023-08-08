#pragma once

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

struct CircleCollider
{
    CircleCollider(float radius) : Radius(radius) {}

    float Radius = 0.0f;
};
