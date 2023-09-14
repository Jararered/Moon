#pragma once

#include "Entity.hpp"

#include <set>

class System
{
public:
    System() = default;
    System(const System&) = default;
    System(System&&) = default;
    System& operator=(const System&) = default;
    System& operator=(System&&) = default;
    virtual ~System() = default;

public:
    virtual void Register() = 0;
    virtual void Initialize() = 0;
    virtual void Update(float dt) = 0;
    virtual void Finalize() = 0;

    std::set<Entity> m_Entities;
};