#include "Camera2D.hpp"

Camera2D::Camera2D()
{
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);

    m_Width = width;
    m_Height = height;
    m_AspectRatio = m_Width / m_Height;
    m_Speed = 100.0f;
}

void Camera2D::Update(float dt)
{
    if (dt < 0.0001f || dt > 0.25f)
        return;

    glm::vec3 positionDelta = { 0.0f, 0.0f, 0.0f };

    // WASD movement
    if (Input::IsKeyPressed(KEY_W))
        positionDelta += glm::vec3(0.0f, 1.0f, 0.0f);
    if (Input::IsKeyPressed(KEY_S))
        positionDelta += glm::vec3(0.0f, -1.0f, 0.0f);
    if (Input::IsKeyPressed(KEY_A))
        positionDelta += glm::vec3(-1.0f, 0.0f, 0.0f);
    if (Input::IsKeyPressed(KEY_D))
        positionDelta += glm::vec3(1.0f, 0.0f, 0.0f);

    // Speed increase
    if (Input::IsKeyPressed(KEY_LEFT_CONTROL))
        m_Speed *= 10.0f;

    m_Position += positionDelta * m_Speed * dt;
    m_ViewMatrix = glm::lookAt(m_Position, (m_Position + m_Direction), glm::vec3(0.0f, 1.0f, 0.0f));
    m_ProjectionMatrix = glm::ortho(-m_Width / 2, m_Width / 2, -m_Height / 2, m_Height / 2, -10.0f, 10.0f);
}