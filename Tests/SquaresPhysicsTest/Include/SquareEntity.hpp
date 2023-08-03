#pragma once

#include <Entity.hpp>

#include "SquareMesh.hpp"

class SquareEntity : public Entity
{
public:
    SquareEntity()
    {
        float size = 50.0f;
        glm::vec3 color = { 1.0f, 1.0f, 1.0f };
        p_Mesh = new SquareMesh(size, color);
    }

    void Update(float dt) override
    {
    }
};