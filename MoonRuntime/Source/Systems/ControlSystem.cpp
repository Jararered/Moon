#include "ControlSystem.hpp"

#include "Input.hpp"
#include "Scenario.hpp"
#include "Signature.hpp"

#include "Component/Control.hpp"
#include "Component/RigidBody.hpp"
#include "Component/Transform.hpp"

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
    m_SpeedLimit = 3.0f;
    m_Name = "Control System";
}

void ControlSystem::Update(float dt)
{
    for (const auto entity : m_Entities)
    {
        const auto jumpMagnitude = 50.0f;
        const auto walkMagnitude = 50.0f;

        auto& transform = m_Scenario->GetComponent<Transform>(entity);
        auto& rigidBody = m_Scenario->GetComponent<RigidBody>(entity);

        // X - Z Movement
        const auto direction = glm::vec3(glm::cos(transform.Rotation.y) * glm::cos(transform.Rotation.x), 0.0f, glm::sin(transform.Rotation.y) * glm::cos(transform.Rotation.x));
        const auto forward = glm::normalize(direction);
        const auto up = glm::vec3(0.0f, 1.0f, 0.0f);
        const auto right = glm::cross(forward, up);

        auto accelerationDirection = glm::vec3(0.0f);

        // WASD movement
        if (Input::IsKeyPressed(Key::W))
            accelerationDirection += forward;
        if (Input::IsKeyPressed(Key::S))
            accelerationDirection -= forward;
        if (Input::IsKeyPressed(Key::A))
            accelerationDirection -= right;
        if (Input::IsKeyPressed(Key::D))
            accelerationDirection += right;

        if (glm::length(accelerationDirection) != 0.0f)
            accelerationDirection = glm::normalize(accelerationDirection);

        if (Input::IsKeyPressed(Key::Space) and rigidBody.MovementStatus == Status::Grounded)
        {
            accelerationDirection += up;
            rigidBody.MovementStatus = Status::Falling;
        }

        // Apply velocity increment
        auto acceleration = glm::vec3(0.0f);
        acceleration.x = walkMagnitude * accelerationDirection.x;
        acceleration.y = jumpMagnitude * accelerationDirection.y;
        acceleration.z = walkMagnitude * accelerationDirection.z;

        rigidBody.Acceleration = acceleration;
        rigidBody.Velocity += rigidBody.Acceleration * dt;
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