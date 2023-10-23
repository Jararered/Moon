#pragma once

#include "Core/SystemInterface.hpp"

class ControlSystem final : public SystemInterface
{
public:
    ControlSystem() = default;
    ControlSystem(const ControlSystem&) = delete;
    ControlSystem(ControlSystem&&) = delete;
    ControlSystem& operator=(const ControlSystem&) = delete;
    ControlSystem& operator=(ControlSystem&&) = delete;
    ~ControlSystem() override = default;

public:
    void Register(std::shared_ptr<Scenario> scenario) override;
    void Initialize() override;
    void Update(float dt) override;
    void UpdateUI() override;
    void Finalize() override;

private:
    float m_SpeedLimit = 0.0f;
    float m_JumpMagnitude = 5.0f;
    float m_WalkMagnitude = 5.0f;
};