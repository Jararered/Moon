#include "Camera2D.hpp"

Camera2D::Camera2D()
{
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
    m_Width = width;
    m_Height = height;
}

void Camera2D::Update(float dt)
{
    // Checks for first frame and if a lag spike occurs
    if (dt < 0.0001f || dt > 0.25f)
        return;

    float velocity = 100.0f;
    glm::vec3 positionChange = { 0.0f, 0.0f, 0.0f };

    // WASD movement
    if (Input::IsKeyPressed(KEY_W))
        positionChange += glm::vec3(0.0f, 1.0f, 0.0f) * velocity;
    if (Input::IsKeyPressed(KEY_S))
        positionChange += glm::vec3(0.0f, -1.0f, 0.0f) * velocity;
    if (Input::IsKeyPressed(KEY_A))
        positionChange += glm::vec3(-1.0f, 0.0f, 0.0f) * velocity;
    if (Input::IsKeyPressed(KEY_D))
        positionChange += glm::vec3(1.0f, 0.0f, 0.0f) * velocity;

    // Speed increase
    if (Input::IsKeyPressed(KEY_LEFT_CONTROL))
        positionChange *= 10.0f;

    m_Position -= positionChange * dt;
    m_ViewMatrix = glm::lookAt(m_Position, (m_Position + m_Direction), glm::vec3(0.0f, 1.0f, 0.0f));
    m_ProjectionMatrix = glm::ortho(-m_Width / 2, m_Width / 2, -m_Height / 2, m_Height / 2, -10.0f, 10.0f);
}