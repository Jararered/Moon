#include "Camera3D.hpp"

Camera3D::Camera3D()
{
    m_FieldOfView = glm::radians(85.0f);
    m_AspectRatio = 16.0f / 9.0f;
    m_NearClip = 0.1f;
    m_FarClip = 10000.0f;
    m_MovementSpeed = 100.0f;

    // Looks toward -z (into screen)
    // +X is right and +Y is up
    m_Yaw = glm::radians(-90.0f);
}

void Camera3D::Update(float dt)
{
    if (dt < 0.0001f || dt > 0.25f)
        return;

    glm::vec3 positionDelta = {0.0f, 0.0f, 0.0f};

    // Set Yaw and Pitch rotations based on mouse movement
    glm::vec2 mouseMovement = Input::GetCapturedMouseMovement();

    // Each pixel the mouse moves is treated as one degree.
    // Scaling each pixel to 0.01 degree
    m_Yaw = m_Yaw + (static_cast<float>(mouseMovement.x) / 400.0f);
    m_Pitch = m_Pitch + (static_cast<float>(mouseMovement.y) / 400.0f);

    // Keep yaw angle from getting to imprecise
    if (m_Yaw > glm::radians(360.0f))
        m_Yaw -= glm::radians(360.0f);
    else if (m_Yaw < glm::radians(-360.0f))
        m_Yaw += glm::radians(360.0f);

    // Keep pitch angle from going too far over
    if (m_Pitch > glm::radians(89.0f))
        m_Pitch = glm::radians(89.0f);
    else if (m_Pitch < glm::radians(-89.0f))
        m_Pitch = glm::radians(-89.0f);

    // Update direction based off of yaw and pitch values
    m_Direction.x = glm::cos(m_Yaw) * glm::cos(m_Pitch);
    m_Direction.y = glm::sin(m_Pitch);
    m_Direction.z = glm::sin(m_Yaw) * glm::cos(m_Pitch);

    // Normalize Direction vector and update Right vector
    m_Direction = glm::normalize(m_Direction);
    m_Right = glm::cross(m_Direction, glm::vec3(0.0f, 1.0f, 0.0f));

    // Basic movement processing
    glm::vec3 newDirection = {0.0f, 0.0f, 0.0f};
    glm::vec3 fowardXZ = {m_Direction.x, 0.0f, m_Direction.z};

    // WASD movement
    if (Input::IsKeyPressed(KEY_W))
        positionDelta += fowardXZ;
    if (Input::IsKeyPressed(KEY_S))
        positionDelta -= fowardXZ;
    if (Input::IsKeyPressed(KEY_A))
        positionDelta -= m_Right;
    if (Input::IsKeyPressed(KEY_D))
        positionDelta += m_Right;

    // Fixes diagonal directed movement to not be faster than along an axis.
    // Only happens when holding two buttons that are off axis from each other.
    if ((positionDelta.x != 0.0f) || (positionDelta.z != 0.0f))
        positionDelta = glm::normalize(positionDelta);

    // Still perform up/down movements after normalization.
    // Don't care about limiting speed along verticals.
    if (Input::IsKeyPressed(KEY_SPACE))
        positionDelta += glm::vec3(0.0f, 1.0f, 0.0f);
    if (Input::IsKeyPressed(KEY_LEFT_SHIFT))
        positionDelta -= glm::vec3(0.0f, 1.0f, 0.0f);

    // Speed increase
    if (Input::IsKeyPressed(KEY_LEFT_CONTROL))
        m_MovementSpeed *= 10.0f;

    m_Position += positionDelta * m_MovementSpeed * dt;
    m_ViewMatrix = glm::lookAt(m_Position, (m_Position + m_Direction), glm::vec3(0.0f, 1.0f, 0.0f));
    m_ProjectionMatrix = glm::perspective(m_FieldOfView, m_AspectRatio, m_NearClip, m_FarClip);
}