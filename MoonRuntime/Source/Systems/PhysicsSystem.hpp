#pragma once

#include "Coordinator.hpp"
#include "System.hpp"

#include "Components/Gravity.hpp"
#include "Components/RigidBody.hpp"
#include "Components/Transform.hpp"

#include <iostream>

extern Coordinator g_Coordinator;

class PhysicsSystem : public System
{
public:
    void Initialize() override { std::cout << "PhysicsSystem::Initialize(): Physics using " << m_SubStepCount << " substeps between each frame.\n"; }

    void Update(float dt) override
    {
        float stepDT = dt / static_cast<float>(m_SubStepCount);

        for (unsigned int step = 0; step < m_SubStepCount; step++)
        {
            for (const auto& entity : m_Entities)
            {
                auto& transform = g_Coordinator.GetComponent<Transform>(entity);
                auto& rigidBody = g_Coordinator.GetComponent<RigidBody>(entity);
                auto& gravity = g_Coordinator.GetComponent<Gravity>(entity);

                transform.Position += rigidBody.Velocity * stepDT;

                rigidBody.Velocity += gravity.Force * stepDT;
            }
        }
    }

    void Finalize() override {}

private:
    unsigned int m_SubStepCount = 4;
};