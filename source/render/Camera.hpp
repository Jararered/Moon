#pragma once

#include <iostream>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>

class Camera
{
public:
    Camera();
    ~Camera();

    void Update(float dt);

public:
    constexpr static glm::vec3 POSITIVE_X = {1.0f, 0.0f, 0.0f};
    constexpr static glm::vec3 POSITIVE_Y = {0.0f, 1.0f, 0.0f};
    constexpr static glm::vec3 POSITIVE_Z = {0.0f, 0.0f, 1.0f};
    constexpr static glm::vec3 WORLD_ORIGIN = {0.0f, 0.0f, 0.0f};
    enum class CameraType
    {
        TwoDimensional,
        ThreeDimensional
    };

private:
    CameraType m_CameraType = CameraType::ThreeDimensional;
    float m_FieldOfView = glm::radians(100.0f);
    float m_AspectRatio = 16.0f / 9.0f;
    float m_NearClip = 0.1f;
    float m_FarClip = 1000.0f;
    float m_Yaw = glm::radians(0.0f);
    float m_Pitch = glm::radians(0.0f);

    glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_Direction = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_Right = {0.0f, 0.0f, 0.0f}; // Cross of Direction and POSITIVE_Y

    glm::mat4 m_ViewMatrix = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    glm::mat4 m_ProjectionMatrix = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

public:
    const glm::mat4 &GetViewMatrix() { return m_ViewMatrix; }
    const glm::mat4 &GetProjectionMatrix() { return m_ProjectionMatrix; }
};