#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
    m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Forward, POSITIVE_Y);
    m_ProjectionMatrix = glm::perspective(m_FieldOfView, m_AspectRatio, m_NearClip, m_FarClip);
}

Camera::~Camera()
{
    std::cout << "Camera::~Camera()\n";
}

void Camera::Update()
{
    m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Forward, POSITIVE_Y);
    m_ProjectionMatrix = glm::perspective(m_FieldOfView, m_AspectRatio, m_NearClip, m_FarClip);
}