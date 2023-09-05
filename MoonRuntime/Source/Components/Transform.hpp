#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

struct Transform
{
    glm::vec3 Position = glm::vec3(0.0f);
    glm::vec3 Rotation = glm::vec3(0.0f);
    glm::vec3 Scale = glm::vec3(1.0f);
};