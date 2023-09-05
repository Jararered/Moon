#include "PhysicsSystem.hpp"

#include "Coordinator.hpp"
#include "Debug.hpp"
#include "System.hpp"

#include "Components/Dynamics.hpp"
#include "Components/Transform.hpp"

#include <iostream>

extern Coordinator g_Coordinator;

void PhysicsSystem::Register()
{
    Signature signature;
    signature.set(g_Coordinator.GetComponentType<Transform>());
    signature.set(g_Coordinator.GetComponentType<Dynamics>());
    g_Coordinator.SetSystemSignature<PhysicsSystem>(signature);
}

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
            auto& dynamics = g_Coordinator.GetComponent<Dynamics>(entity);

            transform.Position += dynamics.Velocity * stepDT;

            dynamics.Velocity += PhysicsSystem::s_Gravity * stepDT;
        }
    }
}

void PhysicsSystem::Finalize()
{
}