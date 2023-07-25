#pragma once

#include "Camera.hpp"

class Camera3D : public Camera
{
public:
    Camera3D() = default;
    virtual ~Camera3D() override = default;

    virtual void Update(float dt) override;

private:
    float m_Yaw = 0.0f;
    float m_Pitch = 0.0f;
    float m_FieldOfView = glm::radians(85.0f);
    float m_AspectRatio = 16.0f / 9.0f;
    float m_NearClip = 0.001f;
    float m_FarClip = 1000.0f;
};