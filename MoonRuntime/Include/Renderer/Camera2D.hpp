#pragma once

#include "Camera.hpp"

class Camera2D : public Camera
{
public:
    Camera2D();
    ~Camera2D() override = default;

    void Update(float dt) override;

private:
    float m_Width = 0.0f;
    float m_Height = 0.0f;
    float m_AspectRatio = 0.0f;
};