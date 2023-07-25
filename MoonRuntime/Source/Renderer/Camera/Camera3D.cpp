#include "Camera3D.hpp"

void Camera3D::Update(float dt)
{
    // Checks for first frame and if a lag spike occurs
    if (dt < 0.0001f || dt > 0.25f)
        return;

    float movementSpeed = dt;

    // Set Yaw and Pitch rotations based on mouse movement
    glm::vec2 mouseMovement = Input::GetMouseMovement();

    // Each pixel the mouse moves is treated as one degree.
    // Scaling each pixel to 0.01 degree
    m_Yaw = m_Yaw + (static_cast<float>(mouseMovement.x) / 100.0f);
    m_Pitch = m_Pitch + (static_cast<float>(mouseMovement.y) / 100.0f);

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

    // Speed increase
    if (Input::IsKeyPressed(KEY_LEFT_CONTROL))
        movementSpeed *= 10.0f;

    // WASD movement
    if (Input::IsKeyPressed(KEY_W))
        newDirection += fowardXZ;
    if (Input::IsKeyPressed(KEY_S))
        newDirection -= fowardXZ;
    if (Input::IsKeyPressed(KEY_A))
        newDirection -= m_Right;
    if (Input::IsKeyPressed(KEY_D))
        newDirection += m_Right;

    // Fixes diagonal directed movement to not be faster than along an axis.
    // Only happens when holding two buttons that are off axis from each other.
    if ((newDirection.x != 0.0f) || (newDirection.z != 0.0f))
        newDirection = glm::normalize(newDirection);

    // Still perform up/down movements after normalization.
    // Don't care about limiting speed along verticals.
    if (Input::IsKeyPressed(KEY_SPACE))
        newDirection += glm::vec3(0.0f, 1.0f, 0.0f);
    if (Input::IsKeyPressed(KEY_LEFT_SHIFT))
        newDirection -= glm::vec3(0.0f, 1.0f, 0.0f);

    m_Position += newDirection * movementSpeed;

    m_ViewMatrix = glm::lookAt(m_Position, (m_Position + m_Direction), glm::vec3(0.0f, 1.0f, 0.0f));
    m_ProjectionMatrix = glm::perspective(m_FieldOfView, m_AspectRatio, m_NearClip, m_FarClip);
}