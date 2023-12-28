#pragma once

#include <Components.hpp>

#include <print>

namespace Moon
{

    struct TestScript : public ScriptInterface
    {
        void Update(float dt, UUID uuid) override
        {
            if (GetScenario()->HasComponent<Transform>(uuid))
            {
                std::println("Entity %d has a transform component!", uuid);
            }
            else
            {
                std::println("Entity %d does not have a transform component!", uuid);
            }
        }
    };

}