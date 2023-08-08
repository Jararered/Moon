#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp>

#include "Input.hpp"

class Camera
{
public:
    Camera() = default;
    virtual ~Camera() = default;

    virtual void Update(float dt){};

protected:
    float m_AspectRatio = 0.0f;
    float m_MovementSpeed = 0.0f;
    float m_ZoomSpeed = 0.0f;
    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_Direction = {0.0f, 0.0f, -1.0f};
    glm::vec3 m_Right = glm::cross(m_Direction, glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 m_ViewMatrix = glm::mat4(0.0f);
    glm::mat4 m_ProjectionMatrix = glm::mat4(0.0f);

public:
    float& GetAspectRatio() { return m_AspectRatio; }
    void SetAspectRatio(float aspectRatio) { m_AspectRatio = aspectRatio; }

    float& GetSpeed() { return m_MovementSpeed; }
    void SetSpeed(float speed) { m_MovementSpeed = speed; }

    glm::vec3& GetPosition() { return m_Position; }
    void SetPosition(const glm::vec3& position) { m_Position = position; }

    glm::vec3& GetDirection() { return m_Direction; }
    void SetDirection(glm::vec3& direction) { m_Direction = direction; }

    glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
    void SetViewMatrix(glm::mat4& viewMatrix) { m_ViewMatrix = viewMatrix; }

    glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
    void SetProjectionMatrix(glm::mat4& projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }
};