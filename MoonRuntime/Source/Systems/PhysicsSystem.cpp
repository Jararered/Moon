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
        for (const auto& entity : m_Entities)
        {
            auto& transform = e_Scenario.GetComponent<Transform>(entity);
            auto& rigidBody = e_Scenario.GetComponent<RigidBody>(entity);

            // const float magnitude = rigidBody.Mass * glm::length(rigidBody.Velocity);

            transform.Position = transform.Position + (rigidBody.Velocity * stepDT);
            rigidBody.Velocity = rigidBody.Velocity + (s_Gravity * stepDT);
        }
    }
}

void PhysicsSystem::Finalize()
{
}

bool PhysicsSystem::IsIntersect(const glm::vec3& lower1, const glm::vec3& lower2, const glm::vec3& upper1, const glm::vec3& upper2)
{
    return ((upper1.x > lower2.x) && (lower1.x < upper2.x) && (upper1.y > lower2.y) && (lower1.y < upper2.y) && (upper1.z > lower2.z) && (lower1.z < upper2.z));
}