#include "PhysicsSystem.hpp"

#include "Component/RigidBody.hpp"
#include "Component/Transform.hpp"
#include "Scenario.hpp"
#include "Utilities/Timer.hpp"

#include <print>

extern Scenario e_Scenario;

void PhysicsSystem::Register()
{
    Signature signature;
    signature.set(e_Scenario.GetComponentType<Transform>());
    signature.set(e_Scenario.GetComponentType<RigidBody>());
    e_Scenario.SetSystemSignature<PhysicsSystem>(signature);
}

void PhysicsSystem::Initialize()
{
    std::println("Physics using {} substeps between each frame.", m_SubStepCount);
}

void PhysicsSystem::Update(float dt)
{
    // Pause physics if frame rate is running slower than 60fps
    if (dt > 1 / 60.0f or dt == 0.0f)
        dt = 1 / 60.0f;
    const auto stepDT = dt / static_cast<float>(m_SubStepCount);

    for (unsigned int step = 0; step < m_SubStepCount; step++)
    {
        for (const auto& e1 : m_Entities)
        {
            auto& transform1 = e_Scenario.GetComponent<Transform>(e1);
            auto& rigidBody1 = e_Scenario.GetComponent<RigidBody>(e1);

            // Ignore any entities without mass
            if (rigidBody1.Mass == 0.0f)
                continue;

            // Update position and velocity w.r.t. time
            transform1.Position += (rigidBody1.Velocity * stepDT);
            rigidBody1.Velocity = rigidBody1.Velocity + (s_Gravity * stepDT);

            // Apply resistances
            rigidBody1.Velocity.x *= 1.0f - m_AirResistance;
            rigidBody1.Velocity.z *= 1.0f - m_AirResistance;

            // Loop through all other entities, including massless entities, to check for collisions
            for (const auto& e2 : m_Entities)
            {
                // Skip collision test if checking against same entity
                if (e1 == e2)
                    continue;

                const auto& transform2 = e_Scenario.GetComponent<Transform>(e2);

                // Check if collision cubes overlap
                if (not IsIntersect(transform1, transform2))
                    continue;

                const auto lower1 = transform1.Position - transform1.Scale / 2.0f;
                const auto upper1 = transform1.Position + transform1.Scale / 2.0f;
                const auto lower2 = transform2.Position - transform2.Scale / 2.0f;
                const auto upper2 = transform2.Position + transform2.Scale / 2.0f;

                const auto x = glm::min(glm::abs(upper1.x - lower2.x), glm::abs(upper2.x - lower1.x));
                const auto y = glm::min(glm::abs(upper1.y - lower2.y), glm::abs(upper2.y - lower1.y));
                const auto z = glm::min(glm::abs(upper1.z - lower2.z), glm::abs(upper2.z - lower1.z));

                // TODO Find better way to resolve collision to where both entities react
                if (x < y and x < z)
                {
                    for (unsigned int i = 0; i < 5; i++)
                    // while (IsIntersect(transform1, transform2))
                    {
                        if (IsIntersect(transform1, transform2))
                            transform1.Position += (-rigidBody1.Velocity * stepDT);
                    }
                    rigidBody1.Velocity.x = -rigidBody1.Velocity.x * rigidBody1.Compressability;
                }
                if (y < x and y < z)
                {
                    for (unsigned int i = 0; i < 5; i++)
                    // while (IsIntersect(transform1, transform2))
                    {
                        if (IsIntersect(transform1, transform2))
                            transform1.Position += (-rigidBody1.Velocity * stepDT);
                    }
                    rigidBody1.Velocity.y = -rigidBody1.Velocity.y * rigidBody1.Compressability;
                }
                if (z < x and z < y)
                {
                    for (unsigned int i = 0; i < 5; i++)
                    // while (IsIntersect(transform1, transform2))
                    {
                        if (IsIntersect(transform1, transform2))
                            transform1.Position += (-rigidBody1.Velocity * stepDT);
                    }
                    rigidBody1.Velocity.z = -rigidBody1.Velocity.z * rigidBody1.Compressability;
                }
            }
        }
    }
}

void PhysicsSystem::Finalize()
{
}

bool PhysicsSystem::IsIntersect(const Transform& transform1, const Transform& transform2)
{
    const auto lower1 = transform1.Position - (transform1.Scale / 2.0f);
    const auto upper1 = transform1.Position + (transform1.Scale / 2.0f);
    const auto lower2 = transform2.Position - (transform2.Scale / 2.0f);
    const auto upper2 = transform2.Position + (transform2.Scale / 2.0f);

    // clang-format off
    return ((upper1.x > lower2.x) and 
            (upper1.y > lower2.y) and 
            (upper1.z > lower2.z) and 
            (upper2.x > lower1.x) and 
            (upper2.y > lower1.y) and 
            (upper2.z > lower1.z));
}