#pragma once

#include "Component/RigidBody.hpp"
#include "Component/Script.hpp"
#include "Component/Transform.hpp"

#include <print>

struct SlowRotate : public ScriptInterface
{
    void Update(Entity entity, float dt) override
    {
        auto& transform = e_Scenario.GetComponent<Transform>(entity);
        transform.Rotation.y += 0.5f * dt;
    }
};

struct MediumRotate : public ScriptInterface
{
    void Update(Entity entity, float dt) override
    {
        auto& transform = e_Scenario.GetComponent<Transform>(entity);
        transform.Rotation.y += dt;
    }
};

struct FastRotate : public ScriptInterface
{
    void Update(Entity entity, float dt) override
    {
        auto& transform = e_Scenario.GetComponent<Transform>(entity);
        transform.Rotation.y += 2.0f * dt;
    }
};