#pragma once

#include "System.hpp"

class CameraSystem final : public System
{
public:
    CameraSystem() = default;
    CameraSystem(const CameraSystem&) = default;
    CameraSystem(CameraSystem&&) = default;
    CameraSystem& operator=(const CameraSystem&) = default;
    CameraSystem& operator=(CameraSystem&&) = default;
    virtual ~CameraSystem() = default;

public:
    void Register() override;
    void Initialize() override;
    void Update(float dt) override;
    void Finalize() override;
};