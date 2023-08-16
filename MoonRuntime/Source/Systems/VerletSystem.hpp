#pragma once

#include "Coordinator.hpp"
#include "System.hpp"

#include "Components/Collider.hpp"
#include "Components/Gravity.hpp"
#include "Components/RigidBody.hpp"
#include "Components/Transform.hpp"

#include <iostream>

extern Coordinator g_Coordinator;

class VerletSystem : public System
{
public:
    void Initialize() override { std::cout << "VerletSystem::Initialize(): Physics using " << m_SubStepCount << " substeps \n"; }

    void Update(float dt) override
    {
        if (dt > 0.016666f) // 60hz at least, prevents physics from dying when hitting lag spikes
            dt = 0.016666f;

        float stepDT = dt / static_cast<float>(m_SubStepCount);

        for (unsigned int step = 0; step < m_SubStepCount; step++)
        {
            for (const auto& entity1 : m_Entities)
            {
                auto& transform1 = g_Coordinator.GetComponent<Transform>(entity1);
                auto& rigidBody1 = g_Coordinator.GetComponent<RigidBody>(entity1);
                const auto& gravity1 = g_Coordinator.GetComponent<Gravity>(entity1);
                const auto& collider1 = g_Coordinator.GetComponent<Collider>(entity1);

                // Accumulate forces
                rigidBody1.Acceleration += gravity1.Force;

                // Check collisions with other entities
                for (const auto& entity2 : m_Entities)
                {
                    if (entity1 == entity2)
                        continue;
                    auto& transform2 = g_Coordinator.GetComponent<Transform>(entity2);
                    const auto& collider2 = g_Coordinator.GetComponent<Collider>(entity2);
                    float distanceMin = collider1.Radius + collider2.Radius;
                    float distanceMag = glm::distance(transform1.Position, transform2.Position);
                    if (distanceMag < distanceMin)
                    {
                        float responseCoef = 0.75f;
                        float delta = 0.5f * responseCoef * (distanceMag - distanceMin);
                        float massRatio1 = collider1.Radius / (collider1.Radius + collider2.Radius);
                        float massRatio2 = collider2.Radius / (collider1.Radius + collider2.Radius);
                        glm::vec3 normal = glm::normalize(transform1.Position - transform2.Position);
                        transform1.Position -= normal * (massRatio2 * delta);
                        transform2.Position += normal * (massRatio1 * delta);
                    }
                }

                // Check constraints
                float constraintRadius = 75.0f;
                glm::vec3 constraintCenter = glm::vec3(0.0f);
                float distanceMag = glm::distance(constraintCenter, transform1.Position);
                if (distanceMag > (constraintRadius - collider1.Radius))
                {
                    glm::vec3 distance = constraintCenter - transform1.Position;
                    glm::vec3 normal = glm::normalize(distance);
                    transform1.Position = constraintCenter - normal * (constraintRadius - collider1.Radius);
                }

                // Update entity
                // Compute how much we moved
                glm::vec3 displacement = transform1.Position - rigidBody1.LastPosition;
                // Update position
                rigidBody1.LastPosition = transform1.Position;
                transform1.Position = transform1.Position + displacement + rigidBody1.Acceleration * (stepDT * stepDT);
                // Reset acceleration
                rigidBody1.Acceleration = glm::vec3(0.0f);
            }
        }
    }

    void Finalize() override {}

private:
    unsigned int m_SubStepCount = 2;
};