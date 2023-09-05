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
        for (const auto& entity1 : m_Entities)
        {
            auto& transform1 = g_Coordinator.GetComponent<Transform>(entity1);
            auto& dynamics1 = g_Coordinator.GetComponent<Dynamics>(entity1);

            const glm::vec3 newPosition = transform1.Position + dynamics1.Velocity * stepDT;
            const glm::vec3 newVelocity = dynamics1.Velocity + s_Gravity * stepDT;

            // Check collisions
            for (const auto& entity2 : m_Entities)
            {
                if (entity1 == entity2)
                    continue;

                const auto& transform2 = g_Coordinator.GetComponent<Transform>(entity2);
                const auto upperbounds1 = transform1.Position + transform1.Scale / 2.0f;
                const auto upperbounds2 = transform2.Position + transform2.Scale / 2.0f;
                const auto lowerbounds1 = transform1.Position - transform1.Scale / 2.0f;
                const auto lowerbounds2 = transform2.Position - transform2.Scale / 2.0f;

                bool intersection = IsIntersect(lowerbounds1, lowerbounds2, upperbounds1, upperbounds2);
                if (intersection)
                {
                    DebugOutput("Wow collision!");
                }
            }

            // Apply new states
            transform1.Position = newPosition;
            dynamics1.Velocity = newVelocity;
        }
    }
}

void PhysicsSystem::Finalize()
{
}

bool PhysicsSystem::IsIntersect(const glm::vec3& lower1, const glm::vec3& lower2, const glm::vec3& upper1, const glm::vec3& upper2)
{
    // Check if Box1's max is greater than Box2's min and Box1's min is less than Box2's max
    return (upper1.x > lower2.x && lower1.x < upper2.x && upper1.y > lower2.y && lower1.y < upper2.y && upper1.z > lower2.z && lower1.z < upper2.z);
}