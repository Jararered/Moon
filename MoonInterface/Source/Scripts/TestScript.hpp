#pragma once

#include "Component/Script.hpp"
#include "Component/TestComponent.hpp"

#include <iostream>

struct TestScript : public ScriptInterface
{
    void Update(std::shared_ptr<Scenario> scenario, EntityID entity, float dt) override
    {
        if (scenario->HasComponent<TestComponent>(entity))
        {
            std::cout << "EntityID " << entity << " has a test component!\n";
        }
        else
        {
            std::cout << "EntityID " << entity << " does not have a test component!\n";
        }
    }
};
