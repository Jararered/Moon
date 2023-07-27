#pragma once

#include "Collider.hpp"

#include <glm/vec3.hpp>

class BoxCollider2D : public Collider
{
public:
    BoxCollider2D() = default;
    ~BoxCollider2D() override = default;
};