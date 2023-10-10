#pragma once

#include "Entity.hpp"
#include "Scenario.hpp"

#include <memory>

struct ScriptInterface
{
    virtual void Update(std::shared_ptr<Scenario> scenario, Entity entity, float dt) = 0;
};

typedef std::shared_ptr<ScriptInterface> Script;