#pragma once

#include <iostream>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>

enum CameraType
{
    Camera2D,
    Camera3D
};

class Camera
{
public:
    Camera(float width, float height, CameraType cameraType);
    ~Camera();

    void Update(float dt);
    void Update2D(float dt);
    void Update3D(float dt);

public:
    constexpr static glm::vec3 POSITIVE_X = {1.0f, 0.0f, 0.0f};
    constexpr static glm::vec3 POSITIVE_Y = {0.0f, 1.0f, 0.0f};
    constexpr static glm::vec3 POSITIVE_Z = {0.0f, 0.0f, 1.0f};
    constexpr static glm::vec3 WORLD_ORIGIN = {0.0f, 0.0f, 0.0f};

private:
    CameraType m_CameraType = CameraType::Camera3D;

    float m_Width = 0.0f, m_Height = 0.0f;
    float m_FieldOfView = glm::radians(85.0f);
    float m_AspectRatio = 16.0f / 9.0f;
    float m_NearClip = 0.001f;
    float m_FarClip = 1000.0f;
    float m_Yaw = 0.0f;
    float m_Pitch = 0.0f;

    glm::vec3 m_Position = {0.0f, 0.0f, 1.0f};
    glm::vec3 m_Direction = {0.0f, 0.0f, -1.0f};
    glm::vec3 m_Right = glm::cross(m_Direction, POSITIVE_Y);

    glm::mat4 m_ViewMatrix = glm::mat4(0.0f);
    glm::mat4 m_ProjectionMatrix = glm::mat4(0.0f);

public:
    const glm::mat4 &GetViewMatrix() { return m_ViewMatrix; }
    const glm::mat4 &GetProjectionMatrix() { return m_ProjectionMatrix; }
};