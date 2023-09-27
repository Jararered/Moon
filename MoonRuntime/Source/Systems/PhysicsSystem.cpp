#include "PhysicsSystem.hpp"

#include "Component/RigidBody.hpp"
#include "Component/Transform.hpp"
#include "Scenario.hpp"
#include "Utilities/Timer.hpp"

#include <glm/trigonometric.hpp>
#include <imgui.h>

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
    m_Name = "Physics System";
    m_SubStepCount = 2;
    m_AirFriction = 10.0f;
    m_SolidFriction = 50.0f;
}

void PhysicsSystem::Update(float dt)
{
    // Pause physics if frame rate is running slower than 60fps
    if (dt > 1 / 60.0f or dt == 0.0f)
        dt = 1 / 60.0f;
    const auto stepDT = dt / static_cast<float>(m_SubStepCount);

    for (const auto e1 : m_Entities)
    {
        auto& transform1 = e_Scenario.GetComponent<Transform>(e1);
        auto& rigidBody1 = e_Scenario.GetComponent<RigidBody>(e1);

        // Ignore any entities without mass
        if (rigidBody1.Mass == 0.0f)
            continue;

        for (unsigned int step = 0; step < m_SubStepCount; step++)
        {
            // Update position and velocity
            rigidBody1.Velocity = rigidBody1.Velocity + (s_Gravity * stepDT);
            transform1.Position += (rigidBody1.Velocity * stepDT);

            // Momentum in X-Z plane
            const auto velocityXZ = glm::vec3(rigidBody1.Velocity.x, 0.0f, rigidBody1.Velocity.z);
            if (glm::length(velocityXZ) > 0.0f)
            {
                const auto momentum = rigidBody1.Mass * glm::length(velocityXZ);
                auto newMomentum = 0.0f;
                if (rigidBody1.MovementStatus == Status::Falling)
                    newMomentum = momentum - glm::min(momentum, m_AirFriction * stepDT);
                if (rigidBody1.MovementStatus == Status::Grounded)
                    newMomentum = momentum - glm::min(momentum, m_SolidFriction * stepDT);
                const auto newVelocityXZ = glm::normalize(velocityXZ) * newMomentum;
                rigidBody1.Velocity.x = newVelocityXZ.x;
                rigidBody1.Velocity.z = newVelocityXZ.z;
            }

            // Loop through all other entities, including massless entities, to check for collisions
            for (const auto e2 : m_Entities)
            {
                // Skip collision test if checking against same entity
                if (e1 == e2)
                    continue;

                const auto& transform2 = e_Scenario.GetComponent<Transform>(e2);

                // Check if collision cubes overlap
                if (not IsIntersect(transform1, transform2))
                    continue;

                const auto lower1 = transform1.Position - transform1.Scale / 2.0f;
                const auto lower2 = transform2.Position - transform2.Scale / 2.0f;
                const auto upper1 = transform1.Position + transform1.Scale / 2.0f;
                const auto upper2 = transform2.Position + transform2.Scale / 2.0f;

                const auto x = glm::min(glm::abs(upper1.x - lower2.x), glm::abs(upper2.x - lower1.x));
                const auto y = glm::min(glm::abs(upper1.y - lower2.y), glm::abs(upper2.y - lower1.y));
                const auto z = glm::min(glm::abs(upper1.z - lower2.z), glm::abs(upper2.z - lower1.z));

                if (x < y and x < z)
                {
                    // +X Collision
                    if (upper1.x > lower2.x and transform1.Position.x < transform2.Position.x)
                    {
                        const auto fix = upper1.x - lower2.x;
                        transform1.Position.x -= fix;
                    }

                    // -X Collision
                    if (lower1.x < upper2.x and transform1.Position.x > transform2.Position.x)
                    {
                        const auto fix = upper2.x - lower1.x;
                        transform1.Position.x += fix;
                    }

                    rigidBody1.Velocity.x = 0.0f;
                    continue;
                }

                if (y < x and y < z)
                {
                    // +Y Collision
                    if (upper1.y > lower2.y and transform1.Position.y < transform2.Position.y)
                    {
                        const auto fix = upper1.y - lower2.y;
                        transform1.Position.y -= fix;
                    }

                    // -Y Collision
                    if (lower1.y < upper2.y and transform1.Position.y > transform2.Position.y)
                    {
                        const auto fix = upper2.y - lower1.y;
                        transform1.Position.y += fix;
                        rigidBody1.MovementStatus = Status::Grounded;
                    }

                    rigidBody1.Velocity.y = 0.0f;
                    continue;
                }

                if (z < x and z < y)
                {
                    // +Z Collision
                    if (upper1.z > lower2.z and transform1.Position.z < transform2.Position.z)
                    {
                        const auto fix = upper1.z - lower2.z;
                        transform1.Position.z -= fix;
                    }

                    // -Z Collision
                    if (lower1.z < upper2.z and transform1.Position.z > transform2.Position.z)
                    {
                        const auto fix = upper2.z - lower1.z;
                        transform1.Position.z += fix;
                    }

                    rigidBody1.Velocity.z = 0.0f;
                    continue;
                }
            }
        }
    }
}

void PhysicsSystem::UpdateUI()
{
    ImGui::InputInt("Steps", &m_SubStepCount);
    ImGui::InputFloat3("Gravity", &s_Gravity.x);
    ImGui::InputFloat("Air Friction", &m_AirFriction, 0.0f, 100.0f);
    ImGui::InputFloat("Solid Friction", &m_SolidFriction, 0.0f, 100.0f);
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