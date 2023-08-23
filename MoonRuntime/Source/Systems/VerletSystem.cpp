#include "VerletSystem.hpp"

#include "Coordinator.hpp"
#include "Debug.hpp"
#include "System.hpp"

#include "Components/Dynamics.hpp"
#include "Components/Gravity.hpp"
#include "Components/Transform.hpp"
#include "Components/Verlet.hpp"

#include <iostream>

extern Coordinator g_Coordinator;

void VerletSystem::Register()
{
    Signature signature;
    signature.set(g_Coordinator.GetComponentType<Transform>());
    signature.set(g_Coordinator.GetComponentType<Gravity>());
    signature.set(g_Coordinator.GetComponentType<Dynamics>());
    signature.set(g_Coordinator.GetComponentType<Verlet>());
    g_Coordinator.SetSystemSignature<VerletSystem>(signature);
}

void VerletSystem::Initialize()
{
    DebugOutput("Physics using " << m_SubStepCount << " substeps");
}

void VerletSystem::Update(float dt)
{
    if (dt > 0.016666f) // 60hz at least, prevents physics from dying when hitting lag spikes
        dt = 0.016666f;

    const float stepDT = dt / static_cast<float>(m_SubStepCount);

    for (unsigned int step = 0; step < m_SubStepCount; step++)
    {
        for (const auto& entity1 : m_Entities)
        {
            auto& transform1 = g_Coordinator.GetComponent<Transform>(entity1);
            auto& dynamics1 = g_Coordinator.GetComponent<Dynamics>(entity1);
            auto& verlet1 = g_Coordinator.GetComponent<Verlet>(entity1);
            const auto& gravity1 = g_Coordinator.GetComponent<Gravity>(entity1);

            // Accumulate forces
            dynamics1.Acceleration += gravity1;

            // Check collisions with other entities
            for (const auto& entity2 : m_Entities)
            {
                if (entity1 == entity2)
                    continue;

                auto& transform2 = g_Coordinator.GetComponent<Transform>(entity2);
                auto& verlet2 = g_Coordinator.GetComponent<Verlet>(entity2);

                const float distanceMin = verlet1.Radius + verlet2.Radius;
                const float distanceMag = glm::distance(transform1.Position, transform2.Position);

                // Process collision
                if (distanceMag < distanceMin)
                {
                    const float responseCoef = 0.75f;
                    const float delta = 0.5f * responseCoef * (distanceMag - distanceMin);
                    const float massRatio1 = verlet1.Radius / (verlet1.Radius + verlet2.Radius);
                    const float massRatio2 = verlet2.Radius / (verlet1.Radius + verlet2.Radius);
                    const glm::vec3 normal = glm::normalize(transform1.Position - transform2.Position);
                    transform1.Position -= normal * (massRatio2 * delta);
                    transform2.Position += normal * (massRatio1 * delta);
                }
            }

            // Check constraints
            const glm::vec3 constraintCenter = glm::vec3(0.0f);
            const float constraintRadius = 75.0f;
            const float distanceMag = glm::distance(constraintCenter, transform1.Position);

            // Process constraints
            if (distanceMag > (constraintRadius - verlet1.Radius))
            {
                glm::vec3 distance = constraintCenter - transform1.Position;
                glm::vec3 normal = glm::normalize(distance);
                transform1.Position = constraintCenter - normal * (constraintRadius - verlet1.Radius);
            }

            // Update entity
            // Compute how much we moved
            const glm::vec3 displacement = transform1.Position - verlet1.LastPosition;
            // Update position
            verlet1.LastPosition = transform1.Position;
            transform1.Position = transform1.Position + displacement + dynamics1.Acceleration * (stepDT * stepDT);
            // Reset acceleration
            dynamics1.Acceleration = glm::vec3(0.0f);
        }
    }
}

void VerletSystem::Finalize()
{
}
