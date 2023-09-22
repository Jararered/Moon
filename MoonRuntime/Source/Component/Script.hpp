#pragma once

#include "Entity.hpp"
#include "Scenario.hpp"

#include <memory>

extern Scenario e_Scenario;

struct ScriptInterface
{
    virtual void Update(Entity entity, float dt) = 0;
};

typedef std::shared_ptr<ScriptInterface> Script;