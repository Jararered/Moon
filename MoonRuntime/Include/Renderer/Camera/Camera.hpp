#pragma once

#include "Input.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp>

class Camera
{
public:
    Camera() = default;
    virtual ~Camera() = default;

    virtual void Update(float dt) {};

public:
    const glm::vec3& Position() { return m_Position; }
    const glm::vec3& Direction() { return m_Direction; }
    const glm::vec3& Right() { return m_Right; }
    const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
    const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }

protected:
    glm::vec3 m_Position = { 0.0f, 0.0f, 1.0f };
    glm::vec3 m_Direction = { 0.0f, 0.0f, -1.0f };
    glm::vec3 m_Right = glm::cross(m_Direction, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 m_ViewMatrix = glm::mat4(0.0f);
    glm::mat4 m_ProjectionMatrix = glm::mat4(0.0f);
};