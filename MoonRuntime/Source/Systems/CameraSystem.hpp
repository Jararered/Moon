#pragma once

#include "SystemInterface.hpp"

class CameraSystem final : public SystemInterface
{
public:
    CameraSystem() = default;
    CameraSystem(const CameraSystem&) = delete;
    CameraSystem(CameraSystem&&) = delete;
    CameraSystem& operator=(const CameraSystem&) = delete;
    CameraSystem& operator=(CameraSystem&&) = delete;
    ~CameraSystem() override = default;

public:
    void Register(std::shared_ptr<Scenario> scenario) override;
    void Initialize() override;
    void Update(float dt) override;
    void UpdateUI() override;
    void Finalize() override;

    void UpdatePerspective(EntityID entity);

private:
    float m_Sensitivity = 0.2f;
};