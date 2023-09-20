#pragma once

#include "Entity.hpp"

#include <set>

class System
{
public:
    System() = default;
    System(const System&) = delete;
    System(System&&) = delete;
    System& operator=(const System&) = delete;
    System& operator=(System&&) = delete;
    virtual ~System() = default;

public:
    virtual void Register() = 0;
    virtual void Initialize() = 0;
    virtual void Update(float dt) = 0;
    virtual void Finalize() = 0;

    std::set<Entity> m_Entities;
};