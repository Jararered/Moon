#include "PhysicsSystem.hpp"

#include "Coordinator.hpp"
#include "Debug.hpp"
#include "System.hpp"

#include "Components/Gravity.hpp"
#include "Components/RigidBody.hpp"
#include "Components/Transform.hpp"

#include <iostream>

extern Coordinator g_Coordinator;

void PhysicsSystem::Initialize()
{
    DebugOutput("Physics using " << m_SubStepCount << " substeps between each frame.");
}

void PhysicsSystem::Update(float dt)
{
    const float stepDT = dt / static_cast<float>(m_SubStepCount);

    for (unsigned int step = 0; step < m_SubStepCount; step++)
    {
        for (const auto& entity : m_Entities)
        {
            auto& transform = g_Coordinator.GetComponent<Transform>(entity);
            auto& rigidBody = g_Coordinator.GetComponent<RigidBody>(entity);
            const auto& gravity = g_Coordinator.GetComponent<Gravity>(entity);

            transform.Position += rigidBody.Velocity * stepDT;

            rigidBody.Velocity += gravity * stepDT;
        }
    }
}

void PhysicsSystem::Finalize()
{
}