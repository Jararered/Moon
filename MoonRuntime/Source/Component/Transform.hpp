#pragma once

#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp>

struct Transform
{
    glm::vec3 Position = glm::vec3(0.0f); // Meter
    glm::vec3 Rotation = glm::vec3(0.0f); // Radian
    glm::vec3 Scale = glm::vec3(1.0f);    // Scalar

    void FixRotation(float& rotation)
    {
        // rotation in radians
        while (rotation > glm::radians(360.0f))
            rotation -= glm::radians(360.0f);
        while (rotation < glm::radians(-360.0f))
            rotation += glm::radians(360.0f);
    }
};