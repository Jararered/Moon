#pragma once

#include <Moon/Components.hpp>

#include <iostream>

namespace Moon
{

    struct TestScript : public ScriptInterface
    {
        void Update(float dt, UUID uuid) override
        {
            if (GetScenario()->HasComponent<Transform>(uuid))
            {
                std::cout << "Entity " << uuid << " has a transform component!\n";
            }
            else
            {
                std::cout << "Entity " << uuid << " does not have a transform component!\n";
            }
        }
    };

}