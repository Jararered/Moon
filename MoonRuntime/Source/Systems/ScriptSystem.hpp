#pragma once

#include "SystemInterface.hpp"

class ScriptSystem final : public SystemInterface
{
public:
    ScriptSystem() = default;
    ScriptSystem(const ScriptSystem&) = delete;
    ScriptSystem(ScriptSystem&&) = delete;
    ScriptSystem& operator=(const ScriptSystem&) = delete;
    ScriptSystem& operator=(ScriptSystem&&) = delete;
    ~ScriptSystem() override = default;

public:
    void Register() override;
    void Initialize() override;
    void Update(float dt) override;
    void UpdateUI() override;
    void Finalize() override;

private:
    float m_TimeScale = 1.0f;
};