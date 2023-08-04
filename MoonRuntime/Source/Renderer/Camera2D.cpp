#include "Camera2D.hpp"

#include <glfw/glfw3.h>

Camera2D::Camera2D()
{
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);

    m_Width = width;
    m_Height = height;
    m_AspectRatio = m_Width / m_Height;
    m_MovementSpeed = 100.0f;
    m_ZoomSpeed = 50.0f;
}

void Camera2D::Update(float dt)
{
    if (dt < 0.0001f || dt > 0.25f)
        return;

    glm::vec3 positionDelta = {0.0f, 0.0f, 0.0f};

    // WASD movement
    if (Input::IsKeyPressed(KEY_W))
        positionDelta += glm::vec3(0.0f, 1.0f, 0.0f);
    if (Input::IsKeyPressed(KEY_S))
        positionDelta += glm::vec3(0.0f, -1.0f, 0.0f);
    if (Input::IsKeyPressed(KEY_A))
        positionDelta += glm::vec3(-1.0f, 0.0f, 0.0f);
    if (Input::IsKeyPressed(KEY_D))
        positionDelta += glm::vec3(1.0f, 0.0f, 0.0f);

    // Zoom in
    if (Input::IsKeyPressed(KEY_EQUAL))
    {
        m_Height -= m_ZoomSpeed * dt * m_ZoomSpeed;
        if (m_Height < 1.0f)
            m_Height = 1.0f; // Prevents view inversion
        m_Width = m_Height * m_AspectRatio;
    }
    // Zoom out
    if (Input::IsKeyPressed(KEY_MINUS))
    {
        m_Height += m_ZoomSpeed * dt * m_ZoomSpeed;
        m_Width = m_Height * m_AspectRatio;
    }

    // Speed increase
    if (Input::IsKeyPressed(KEY_LEFT_CONTROL))
        m_MovementSpeed *= 10.0f;

    m_Position += positionDelta * m_MovementSpeed * dt;
    // m_Position += positionDelta * m_MovementSpeed * dt * m_Height / 500.0f;
    m_ViewMatrix = glm::lookAt(m_Position, (m_Position + m_Direction), glm::vec3(0.0f, 1.0f, 0.0f));
    m_ProjectionMatrix = glm::ortho(-m_Width / 2, m_Width / 2, -m_Height / 2, m_Height / 2, -10.0f, 10.0f);
}