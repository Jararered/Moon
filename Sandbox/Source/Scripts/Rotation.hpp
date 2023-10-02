#pragma once

#include "Component/RigidBody.hpp"
#include "Component/Script.hpp"
#include "Component/Transform.hpp"

#include <glm/trigonometric.hpp>

struct RotateScript : public ScriptInterface
{
    RotateScript(float speed) : m_Speed(speed) {}

    void Update(std::shared_ptr<Scenario> scenario, Entity entity, float dt) override
    {
        auto& transform = scenario->GetComponent<Transform>(entity);
        transform.Rotation.y += m_Speed * dt;
        transform.FixRotation(transform.Rotation.y);
    }

private:
    float m_Speed = glm::radians(360.0f);
};
