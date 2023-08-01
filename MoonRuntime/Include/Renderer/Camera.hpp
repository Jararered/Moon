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
    glm::vec3& GetPosition() { return m_Position; }
    glm::vec3& GetDirection() { return m_Direction; }
    glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
    glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }

    float GetAspectRatio() const { return m_AspectRatio; }
    void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }

    float GetSpeed() const { return m_Speed; }
    void SetSpeed(float speed) { m_Speed = speed; }

    glm::vec3 GetPosition() const { return m_Position; }
    void SetPosition(const glm::vec3& position) { m_Position = position; }

protected:
    float m_AspectRatio = 0.0f;
    float m_Speed = 0.0f;
    glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_Direction = { 0.0f, 0.0f, -1.0f };
    glm::vec3 m_Right = glm::cross(m_Direction, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 m_ViewMatrix = glm::mat4(0.0f);
    glm::mat4 m_ProjectionMatrix = glm::mat4(0.0f);
};