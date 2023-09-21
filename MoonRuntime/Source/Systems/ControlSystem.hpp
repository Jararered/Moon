#pragma once

#include "System.hpp"

class ControlSystem final : public System
{
public:
    ControlSystem() = default;
    ControlSystem(const ControlSystem&) = delete;
    ControlSystem(ControlSystem&&) = delete;
    ControlSystem& operator=(const ControlSystem&) = delete;
    ControlSystem& operator=(ControlSystem&&) = delete;
    ~ControlSystem() override = default;

public:
    void Register() override;
    void Initialize() override;
    void Update(float dt) override;
    void Finalize() override;
};