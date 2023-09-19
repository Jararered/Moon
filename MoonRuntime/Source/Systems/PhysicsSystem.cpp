#include "PhysicsSystem.hpp"

#include "Coordinator.hpp"

#include "Components/Dynamics.hpp"
#include "Components/Transform.hpp"

#include <print>

extern Coordinator e_Coordinator;

void PhysicsSystem::Register()
{
    Signature signature;
    signature.set(e_Coordinator.GetComponentType<Transform>());
    signature.set(e_Coordinator.GetComponentType<Dynamics>());
    e_Coordinator.SetSystemSignature<PhysicsSystem>(signature);
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
        for (const auto& entity1 : m_Entities)
        {
            auto& transform = e_Coordinator.GetComponent<Transform>(entity1);
            auto& dynamics = e_Coordinator.GetComponent<Dynamics>(entity1);

            transform.Position = transform.Position + (dynamics.Velocity * stepDT);
            dynamics.Velocity = dynamics.Velocity + (s_Gravity * stepDT);
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