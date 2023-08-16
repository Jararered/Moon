#pragma once

#include <glm/mat4x4.hpp>

struct Camera
{
    glm::mat4 ViewMatrix = glm::mat4(1.0f);
    glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
};