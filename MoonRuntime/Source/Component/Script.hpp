#pragma once

#include "Core/Entity.hpp"
#include "Core/Scenario.hpp"

#include <memory>

struct ScriptInterface
{
    virtual void Update(std::shared_ptr<Scenario> scenario, UUID entity, float dt) = 0;
};

typedef std::shared_ptr<ScriptInterface> Script;