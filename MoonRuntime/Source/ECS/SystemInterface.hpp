#pragma once

#include "Entity.hpp"

#include <imgui.h>
#include <set>
#include <string>

class SystemInterface
{
public:
    SystemInterface() = default;
    SystemInterface(const SystemInterface&) = delete;
    SystemInterface(SystemInterface&&) = delete;
    SystemInterface& operator=(const SystemInterface&) = delete;
    SystemInterface& operator=(SystemInterface&&) = delete;
    virtual ~SystemInterface() = default;

public:
    virtual void Register() = 0;
    virtual void Initialize() = 0;
    virtual void Update(float dt) = 0;
    virtual void Finalize() = 0;

    std::string m_Name;
    std::set<Entity> m_Entities;
};