#include "PhysicsSystem.hpp"

#include "Scenario.hpp"
#include "Utilities/Timer.hpp"

#include <glm/trigonometric.hpp>
#include <imgui.h>

void PhysicsSystem::Register(std::shared_ptr<Scenario> scenario)
{
    m_Scenario = scenario;

    Signature signature;
    signature.set(m_Scenario->GetComponentType<Transform>());
    signature.set(m_Scenario->GetComponentType<RigidBody>());
    m_Scenario->SetSystemSignature<PhysicsSystem>(signature);
}

void PhysicsSystem::Initialize()
{
    m_Name = "Physics System";
    m_SubStepCount = 4;
    m_AirFrictionCoefficient = 30.0f;
    m_SolidFrictionCoefficient = 50.0f;
    m_Gravity = glm::vec3(0.0f, -15.0f, 0.0f);
}

void PhysicsSystem::Update(float dt)
{
    // Ensures physics will always run at a minimum of 60hz
    if (dt > 1.0f / 60.0f or dt == 0.0f)
        dt = 1.0f / 60.0f;
    dt = dt / static_cast<float>(m_SubStepCount);

    for (const auto entity : m_Entities)
    {
        auto& rigidBody1 = m_Scenario->GetComponent<RigidBody>(entity);

        // Ignore any entities without mass
        if (rigidBody1.Mass == 0.0f)
            continue;

        for (unsigned int step = 0; step < m_SubStepCount; step++)
        {
            UpdateStep(dt, entity);
            UpdateFriction(dt, entity);
            UpdateCollision(dt, entity);
        }
    }
}

void PhysicsSystem::UpdateUI()
{
    ImGui::InputInt("Steps", &m_SubStepCount);
    ImGui::InputFloat3("Gravity", &m_Gravity.x);
    ImGui::InputFloat("Air Friction", &m_AirFrictionCoefficient, 0.0f, 100.0f);
    ImGui::InputFloat("Solid Friction", &m_SolidFrictionCoefficient, 0.0f, 100.0f);
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
    // clang-format on
}

void PhysicsSystem::UpdateStep(float dt, Entity entity)
{
    auto& transform = m_Scenario->GetComponent<Transform>(entity);
    auto& rigidBody = m_Scenario->GetComponent<RigidBody>(entity);

    // Update position and velocity
    rigidBody.Velocity = rigidBody.Velocity + (m_Gravity * dt);
    transform.Position = transform.Position + (rigidBody.Velocity * dt);
}

void PhysicsSystem::UpdateCollision(float dt, Entity entity)
{
    auto& transform1 = m_Scenario->GetComponent<Transform>(entity);
    auto& rigidBody1 = m_Scenario->GetComponent<RigidBody>(entity);

    for (const auto other : m_Entities)
    {
        // Skip collision test if checking against same entity
        if (entity == other)
            continue;

        auto& transform2 = m_Scenario->GetComponent<Transform>(other);

        // Check if collision cubes overlap
        if (not IsIntersect(transform1, transform2))
            continue;

        auto& rigidBody2 = m_Scenario->GetComponent<RigidBody>(other);

        const auto lower1 = transform1.Position - transform1.Scale / 2.0f;
        const auto lower2 = transform2.Position - transform2.Scale / 2.0f;
        const auto upper1 = transform1.Position + transform1.Scale / 2.0f;
        const auto upper2 = transform2.Position + transform2.Scale / 2.0f;

        const auto x = glm::min(glm::abs(upper1.x - lower2.x), glm::abs(upper2.x - lower1.x));
        const auto y = glm::min(glm::abs(upper1.y - lower2.y), glm::abs(upper2.y - lower1.y));
        const auto z = glm::min(glm::abs(upper1.z - lower2.z), glm::abs(upper2.z - lower1.z));

        if (x < y and x < z)
        {
            // Fix position
            if (upper1.x > lower2.x and transform1.Position.x < transform2.Position.x)
                transform1.Position.x -= upper1.x - lower2.x;
            if (lower1.x < upper2.x and transform1.Position.x > transform2.Position.x)
                transform1.Position.x += upper2.x - lower1.x;

            auto momentum = rigidBody1.Mass * glm::abs(rigidBody1.Velocity.x);
            auto newVelocity = 0.0f;
            if (rigidBody1.Velocity.x < 0.0f)
                newVelocity = -momentum / rigidBody1.Mass;
            else
                newVelocity = momentum / rigidBody1.Mass;

            rigidBody1.Velocity.x = newVelocity;

            continue;
        }

        if (y < x and y < z)
        {
            // Fix position
            if (upper1.y > lower2.y and transform1.Position.y < transform2.Position.y)
                transform1.Position.y -= upper1.y - lower2.y;
            if (lower1.y < upper2.y and transform1.Position.y > transform2.Position.y)
            {
                transform1.Position.y += upper2.y - lower1.y;
                rigidBody1.MovementStatus = Status::Grounded;
            }

            rigidBody1.Velocity.y = 0.0f;

            continue;
        }

        if (z < x and z < y)
        {
            // Fix position
            if (upper1.z > lower2.z and transform1.Position.z < transform2.Position.z)
                transform1.Position.z -= upper1.z - lower2.z;
            if (lower1.z < upper2.z and transform1.Position.z > transform2.Position.z)
                transform1.Position.z += upper2.z - lower1.z;

            auto momentum = rigidBody1.Mass * glm::abs(rigidBody1.Velocity.z);
            auto newVelocity = 0.0f;
            if (rigidBody1.Velocity.z < 0.0f)
                newVelocity = -momentum / rigidBody1.Mass;
            else
                newVelocity = momentum / rigidBody1.Mass;

            rigidBody1.Velocity.z = newVelocity;

            continue;
        }
    }
}

void PhysicsSystem::UpdateFriction(float dt, Entity entity)
{
    auto& rigidBody = m_Scenario->GetComponent<RigidBody>(entity);

    // Momentum in X-Z plane
    const auto velocityXZ = glm::vec3(rigidBody.Velocity.x, 0.0f, rigidBody.Velocity.z);
    if (glm::length(velocityXZ) > 0.0f)
    {
        const auto momentum = rigidBody.Mass * glm::length(velocityXZ);
        auto newMomentum = 0.0f;

        if (rigidBody.MovementStatus == Status::Falling)
            newMomentum = momentum - glm::min(momentum, m_AirFrictionCoefficient * dt);
        if (rigidBody.MovementStatus == Status::Grounded)
            newMomentum = momentum - glm::min(momentum, m_SolidFrictionCoefficient * dt);

        const auto newVelocityXZ = glm::normalize(velocityXZ) * newMomentum / rigidBody.Mass;
        rigidBody.Velocity.x = newVelocityXZ.x;
        rigidBody.Velocity.z = newVelocityXZ.z;
    }
}