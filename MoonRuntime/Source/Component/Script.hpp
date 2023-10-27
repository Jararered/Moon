#pragma once

#include "Core/Entity.hpp"
#include "Core/Scenario.hpp"

#include <memory>

namespace Moon
{

    struct ScriptInterface
    {
        static std::shared_ptr<Scenario> s_Scenario;

        virtual void Update(float dt, UUID uuid) = 0;
    };

    typedef std::shared_ptr<ScriptInterface> Script;

}