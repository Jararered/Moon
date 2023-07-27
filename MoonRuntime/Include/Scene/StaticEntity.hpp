#pragma once

#include "Entity.hpp"

class StaticEntity : public Entity
{
public:
    StaticEntity() = default;

    virtual void Initialize(float dt) override {}
    virtual void Update(float dt) override {}
    virtual void Finalize(float dt) override {}
};