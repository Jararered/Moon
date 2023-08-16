#pragma once

#include <set>

#include "Entity.hpp"

class System
{
public:
    virtual void Initialize() = 0;
    virtual void Update(float dt) = 0;
    virtual void Finalize() = 0;

    std::set<Entity> m_Entities;
};