#pragma once

#include "System.hpp"

class ScriptSystem final : public System
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
    void Finalize() override;
};