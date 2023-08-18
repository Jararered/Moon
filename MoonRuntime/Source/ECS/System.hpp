#pragma once

#include <set>

#include "Entity.hpp"

class System
{
public:
    System() = default;
    virtual ~System() = default;

    virtual void Initialize() = 0;
    virtual void Update(float dt) = 0;
    virtual void Finalize() = 0;

    std::set<Entity> m_Entities;
};