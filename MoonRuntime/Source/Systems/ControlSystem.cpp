#include "ControlSystem.hpp"

#include "Core/Input.hpp"
#include "Core/Scenario.hpp"
#include "Core/Signature.hpp"

#include "Components/Control.hpp"
#include "Components/RigidBody.hpp"
#include "Components/Transform.hpp"

#include <glm/trigonometric.hpp>
#include <imgui.h>

void ControlSystem::Register(std::shared_ptr<Scenario> scenario)
{
    m_Scenario = scenario;

    Signature signature;
    signature.set(m_Scenario->GetComponentType<Transform>());
    signature.set(m_Scenario->GetComponentType<Control>());
    signature.set(m_Scenario->GetComponentType<RigidBody>());
    m_Scenario->SetSystemSignature<ControlSystem>(signature);
}

void ControlSystem::Initialize()
{
    m_SpeedLimit = 2.0f;
    m_Name = "Control System";
}

void ControlSystem::Update(float dt)
{
    for (const auto entity : m_Entities)
    {
        const auto jumpMagnitude = 5.0f;
        const auto walkMagnitude = 5.0f;

        auto& transform = m_Scenario->GetComponent<Transform>(entity);
        auto& rigidBody = m_Scenario->GetComponent<RigidBody>(entity);

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

        if (Input::IsKeyPressed(Key::Space) and rigidBody.MovementStatus == Status::Grounded)
        {
            velocityDirection += up;
            rigidBody.MovementStatus = Status::Falling;
        }

        // Apply velocity increment
        auto velocity = glm::vec3(0.0f);
        velocity.x = walkMagnitude * velocityDirection.x;
        velocity.y = jumpMagnitude * velocityDirection.y;
        velocity.z = walkMagnitude * velocityDirection.z;
        rigidBody.Velocity += velocity;

        // Limit velocity in x,z directions
        auto xz = glm::vec3(rigidBody.Velocity.x, 0.0f, rigidBody.Velocity.z);
        if (glm::length(xz) > m_SpeedLimit and glm::length(xz) != 0.0f)
        {
            auto newxz = glm::normalize(xz) * m_SpeedLimit;
            rigidBody.Velocity.x = newxz.x;
            rigidBody.Velocity.z = newxz.z;
        }
    }
}

void ControlSystem::UpdateUI()
{
    for (const auto entity : m_Entities)
    {
        auto& transform = m_Scenario->GetComponent<Transform>(entity);
        auto& rigidBody = m_Scenario->GetComponent<RigidBody>(entity);

        ImGui::LabelText("", "Rigid Body");
        ImGui::InputFloat3("Position", &transform.Position.x);
        ImGui::InputFloat3("Velocity", &rigidBody.Velocity.x);
        ImGui::InputFloat3("Acceleration", &rigidBody.Acceleration.x);
    }
}

void ControlSystem::Finalize()
{
}