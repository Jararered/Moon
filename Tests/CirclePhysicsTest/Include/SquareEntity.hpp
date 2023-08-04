#pragma once

#include <Entity.hpp>

#include "SquareMesh.hpp"

class SquareEntity : public Entity
{
public:
    SquareEntity() = default;
    ~SquareEntity() = default;

    void Update(float dt) override
    {
        const glm::vec3 gravity = {0.0f, -1000.0f, 0.0f};
        ApplyAcceleration(gravity);

        UpdateDynamics(dt);
    }
};