#include "ControlSystem.hpp"

#include "Components.hpp"
#include "Input.hpp"

#include <glm/trigonometric.hpp>

using namespace Moon;

void ControlSystem::Register(std::shared_ptr<Scenario> scenario)
{
    m_Scenario = scenario;

    Signature signature;
    signature.set(m_Scenario->GetComponentType<Transform>());
    signature.set(m_Scenario->GetComponentType<Controller>());
    signature.set(m_Scenario->GetComponentType<RigidBody>());
    m_Scenario->SetSystemSignature<ControlSystem>(signature);
}

void ControlSystem::Initialize()
{
}

void ControlSystem::Update(float)
{
    for (const auto entity : m_Entities)
    {
        auto& transform = m_Scenario->GetComponent<Transform>(entity);
        auto& rigidBody = m_Scenario->GetComponent<RigidBody>(entity);
        auto controller = m_Scenario->GetComponent<Controller>(entity);

        // X - Z Movement
        const auto direction = glm::vec3(glm::cos(transform.Rotation.y) * glm::cos(transform.Rotation.x), 0.0f, glm::sin(transform.Rotation.y) * glm::cos(transform.Rotation.x));
        const auto forward = glm::normalize(direction);
        const auto up = glm::vec3(0.0f, 1.0f, 0.0f);
        const auto right = glm::cross(forward, up);

        auto velocityDirection = glm::vec3(0.0f);

        // WASD movement
        if (Input::IsKeyPressed(Key::W))
            velocityDirection += forward;
        if (Input::IsKeyPressed(Key::S))
            velocityDirection -= forward;
        if (Input::IsKeyPressed(Key::A))
            velocityDirection -= right;
        if (Input::IsKeyPressed(Key::D))
            velocityDirection += right;

        if (glm::length(velocityDirection) != 0.0f)
            velocityDirection = glm::normalize(velocityDirection);

        if (Input::IsKeyPressed(Key::Space) and rigidBody.MovementStatus == RigidBody::Status::Grounded)
        {
            velocityDirection += up;
            rigidBody.MovementStatus = RigidBody::Status::Falling;
        }

        // Apply velocity increment
        auto velocity = glm::vec3(0.0f);
        velocity.x = controller.WalkMagnitude * velocityDirection.x;
        velocity.y = controller.JumpMagnitude * velocityDirection.y;
        velocity.z = controller.WalkMagnitude * velocityDirection.z;
        rigidBody.Velocity += velocity;

        if (Input::IsKeyPressed(Key::LeftControl))
            controller.SpeedLimit *= 1.5f;
        if (Input::IsKeyPressed(Key::LeftShift))
            controller.SpeedLimit *= 0.5f;

        // Limit velocity in x,z directions
        auto xz = glm::vec3(rigidBody.Velocity.x, 0.0f, rigidBody.Velocity.z);
        if (glm::length(xz) > controller.SpeedLimit and glm::length(xz) != 0.0f)
        {
            auto newxz = glm::normalize(xz) * controller.SpeedLimit;
            rigidBody.Velocity.x = newxz.x;
            rigidBody.Velocity.z = newxz.z;
        }
    }
}

void ControlSystem::Finalize()
{
}
