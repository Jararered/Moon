#pragma once

#include "Core/Scenario/Scenario.hpp"
#include "Core/Scenario/UUID.hpp"

#include <memory>

namespace Moon
{

    class ScriptInterface
    {
    public:
        virtual void Update(float dt, UUID uuid) = 0;

        std::shared_ptr<Scenario> GetScenario() { return s_Scenario.lock(); }

    private:
        static std::weak_ptr<Scenario> s_Scenario;
    };

    using Script = std::weak_ptr<ScriptInterface>;

}