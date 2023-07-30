#pragma once

#include "Camera.hpp"

class Camera3D : public Camera
{
public:
    Camera3D();
    ~Camera3D() override = default;

    void Update(float dt) override;

private:
    float m_Yaw = 0.0f;
    float m_Pitch = 0.0f;
    float m_FieldOfView = 0.0f;
    float m_NearClip = 0.0f;
    float m_FarClip = 0.0f;
};