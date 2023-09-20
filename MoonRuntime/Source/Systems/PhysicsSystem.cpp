#include "PhysicsSystem.hpp"

#include "Component/RigidBody.hpp"
#include "Component/Transform.hpp"
#include "Scenario.hpp"

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
    const auto stepDT = dt / static_cast<float>(m_SubStepCount);

    for (unsigned int step = 0; step < m_SubStepCount; step++)
    {
        for (const auto& e1 : m_Entities)
        {
            auto& transform1 = e_Scenario.GetComponent<Transform>(e1);
            auto& rigidBody1 = e_Scenario.GetComponent<RigidBody>(e1);

            if (rigidBody1.Mass == 0.0f)
                continue;

            auto newPosition1 = transform1.Position + (rigidBody1.Velocity * stepDT);
            auto newVelocity1 = rigidBody1.Velocity + (s_Gravity * stepDT);

            for (const auto& e2 : m_Entities)
            {
                if (e1 == e2)
                    continue;

                const auto& transform2 = e_Scenario.GetComponent<Transform>(e2);
                const auto& rigidBody2 = e_Scenario.GetComponent<RigidBody>(e2);

                const auto lower1 = newPosition1 - (transform1.Scale / 2.0f);
                const auto upper1 = newPosition1 + (transform1.Scale / 2.0f);
                const auto lower2 = transform2.Position - (transform2.Scale / 2.0f);
                const auto upper2 = transform2.Position + (transform2.Scale / 2.0f);

                if (!IsIntersect(lower1, lower2, upper1, upper2))
                    continue;

                const auto x = glm::min(glm::abs(upper1.x - lower2.x), glm::abs(upper2.x - lower1.x));
                const auto y = glm::min(glm::abs(upper1.y - lower2.y), glm::abs(upper2.y - lower1.y));
                const auto z = glm::min(glm::abs(upper1.z - lower2.z), glm::abs(upper2.z - lower1.z));

                if (x < y && x < z)
                {
                    newPosition1.x = transform1.Position.x;
                    newVelocity1.x *= -1.0f;
                }
                if (y < x && y < z)
                {
                    newPosition1.y = transform1.Position.y;
                    newVelocity1.y *= -1.0f;
                }
                if (z < x && z < y)
                {
                    newPosition1.z = transform1.Position.z;
                    newVelocity1.z *= -1.0f;
                }
            }

            transform1.Position = newPosition1;
            rigidBody1.Velocity = newVelocity1;
        }
    }
}

void PhysicsSystem::Finalize()
{
}

bool PhysicsSystem::IsIntersect(const glm::vec3& lower1, const glm::vec3& lower2, const glm::vec3& upper1, const glm::vec3& upper2)
{
    // clang-format off
    return ((upper1.x > lower2.x) && 
            (upper1.y > lower2.y) && 
            (upper1.z > lower2.z) && 
            (upper2.x > lower1.x) && 
            (upper2.y > lower1.y) && 
            (upper2.z > lower1.z));
}