#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include "input/Input.hpp"

Camera::Camera(float width, float height, CameraType cameraType)
    : m_Width(width), m_Height(height), m_AspectRatio(width / height), m_CameraType(cameraType)
{
}

Camera::~Camera()
{
    std::cout << "Camera::~Camera()" << std::endl;
}

void Camera::Update(float dt)
{
    // Checks for first frame and if a lag spike occurs
    if (dt < 0.0001f || dt > 0.25f)
        return;

    if (m_CameraType == CameraType::Camera2D)
    {
        Update2D(dt);
    }
    if (m_CameraType == CameraType::Camera3D)
    {
        Update3D(dt);
    }

    std::cout << "Position: " << m_Position.x << ", " << m_Position.y << ", " << m_Position.z << std::endl;
}

void Camera::Update2D(float dt)
{
    float movementSpeed = dt;

    // Speed increase
    if (Input::IsKeyPressed(KEY_LEFT_CONTROL))
        movementSpeed *= 10.0f;

    // WASD movement
    if (Input::IsKeyPressed(KEY_W))
        m_Position += +POSITIVE_Y * movementSpeed;
    if (Input::IsKeyPressed(KEY_S))
        m_Position += -POSITIVE_Y * movementSpeed;
    if (Input::IsKeyPressed(KEY_A))
        m_Position += -POSITIVE_X * movementSpeed;
    if (Input::IsKeyPressed(KEY_D))
        m_Position += +POSITIVE_X * movementSpeed;

    m_ViewMatrix = glm::lookAt(m_Position, (m_Position + m_Direction), POSITIVE_Y);
    m_ProjectionMatrix = glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -10.0f, 10.0f);
}

void Camera::Update3D(float dt)
{
    float movementSpeed = dt;

    // Set Yaw and Pitch rotations based on mouse movement
    glm::vec2 mouseMovement = Input::GetMouseMovement();

    // Each pixel the mouse moves is treated as one degree.
    // Scaling each pixel to 0.01 degree
    m_Yaw = m_Yaw + (static_cast<float>(mouseMovement.x) / 100.0f);
    m_Pitch = m_Pitch + (static_cast<float>(mouseMovement.y) / 100.0f);

    std::cout << "MouseX: " << mouseMovement.x << ", MouseY: " << mouseMovement.y << std::endl;
    std::cout << "Yaw: " << m_Yaw << ", Pitch: " << m_Pitch << std::endl;

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
    m_Right = glm::cross(m_Direction, Camera::POSITIVE_Y);

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
        newDirection += Camera::POSITIVE_Y;
    if (Input::IsKeyPressed(KEY_LEFT_SHIFT))
        newDirection -= Camera::POSITIVE_Y;

    m_Position += newDirection * movementSpeed;

    m_ViewMatrix = glm::lookAt(m_Position, (m_Position + m_Direction), POSITIVE_Y);
    m_ProjectionMatrix = glm::perspective(m_FieldOfView, m_AspectRatio, m_NearClip, m_FarClip);
}