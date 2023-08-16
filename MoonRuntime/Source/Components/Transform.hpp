#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

struct Transform
{
    glm::vec3 Position = {0.0f, 0.0f, 0.0f};
    glm::vec3 Rotation = {0.0f, 0.0f, 0.0f};
    glm::vec3 Scale = {1.0f, 1.0f, 1.0f};
};