#pragma once

#include "System.hpp"

class CameraSystem final : public System
{
public:
    CameraSystem() = default;
    CameraSystem(const CameraSystem&) = delete;
    CameraSystem(CameraSystem&&) = delete;
    CameraSystem& operator=(const CameraSystem&) = delete;
    CameraSystem& operator=(CameraSystem&&) = delete;
    ~CameraSystem() override = default;

public:
    void Register() override;
    void Initialize() override;
    void Update(float dt) override;
    void Finalize() override;
};