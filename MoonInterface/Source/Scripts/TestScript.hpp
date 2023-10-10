#pragma once

#include "Component/Script.hpp"
#include "Component/TestComponent.hpp"

#include <iostream>

struct TestScript : public ScriptInterface
{
    void Update(std::shared_ptr<Scenario> scenario, Entity entity, float dt) override
    {
        if (scenario->HasComponent<TestComponent>(entity))
        {
            std::cout << "Entity " << entity << " has a test component!\n";
        }
        else
        {
            std::cout << "Entity " << entity << " does not have a test component!\n";
        }
    }
};
