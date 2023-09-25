#include "ControlSystem.hpp"

#include "Input.hpp"
#include "Scenario.hpp"
#include "Signature.hpp"

#include "Component/Control.hpp"
#include "Component/RigidBody.hpp"
#include "Component/Transform.hpp"

#include <glm/trigonometric.hpp>
#include <imgui.h>

extern Scenario e_Scenario;

void ControlSystem::Register()
{
    Signature signature;
    signature.set(e_Scenario.GetComponentType<Transform>());
    signature.set(e_Scenario.GetComponentType<Control>());
    signature.set(e_Scenario.GetComponentType<RigidBody>());
    e_Scenario.SetSystemSignature<ControlSystem>(signature);
}

void ControlSystem::Initialize()
{
    m_SpeedLimit = 5.0f;
}

void ControlSystem::Update(float dt)
{
    for (const auto entity : m_Entities)
    {
        auto& transform = e_Scenario.GetComponent<Transform>(entity);
        auto& rigidBody = e_Scenario.GetComponent<RigidBody>(entity);

        ImGui::Begin("Control Settings");
        ImGui::SliderFloat("Limit", &m_SpeedLimit, 0.0f, 10.0f);
        ImGui::SliderFloat3("Velocity", &rigidBody.Velocity.x, 0.0f, 10.0f);
        ImGui::End();

        // X - Z Movement
        auto direction = glm::vec3(0.0f);
        direction.x = glm::cos(transform.Rotation.y) * glm::cos(transform.Rotation.x);
        direction.y = glm::sin(transform.Rotation.x);
        direction.z = glm::sin(transform.Rotation.y) * glm::cos(transform.Rotation.x);
        direction = glm::normalize(direction);

        auto speedLimit = m_SpeedLimit;
        if (Input::IsKeyPressed(Key::LeftControl))
            speedLimit *= 2.0f;
        if (Input::IsKeyPressed(Key::LeftShift))
            speedLimit *= 0.5f;

        const auto right = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));
        const auto forward = glm::vec3(direction.x, 0.0f, direction.z);

        // WASD movement
        auto velocityDelta = glm::vec3(0.0f);
        if (Input::IsKeyPressed(Key::W))
            velocityDelta += forward;
        if (Input::IsKeyPressed(Key::S))
            velocityDelta -= forward;
        if (Input::IsKeyPressed(Key::A))
            velocityDelta -= right;
        if (Input::IsKeyPressed(Key::D))
            velocityDelta += right;

        // Fixes diagonal directed movement to not be faster than along an axis.
        // Only happens when holding two buttons that are off axis from each other.
        if (velocityDelta.x != 0.0f or velocityDelta.z != 0.0f)
            velocityDelta = glm::normalize(velocityDelta);

        // Y Movement
        // Still perform up/down movements after normalization.
        // Don't care about limiting speed along verticals.
        if (Input::IsKeyPressed(Key::Space) and rigidBody.MovementStatus == Status::Grounded)
        {
            velocityDelta.y += 5.0f;
            rigidBody.MovementStatus = Status::Falling;
        }

        // Apply velocity increment
        rigidBody.Velocity += velocityDelta;

        // Check velocity in x - z plane, limit magnitude
        const auto velocityXZ = glm::vec3(rigidBody.Velocity.x, 0.0f, rigidBody.Velocity.z);
        if (glm::length(velocityXZ) > speedLimit)
        {
            const auto clampedVelocityXZ = glm::normalize(velocityXZ) * speedLimit;
            rigidBody.Velocity.x = clampedVelocityXZ.x;
            rigidBody.Velocity.z = clampedVelocityXZ.z;
        }
    }
}

void ControlSystem::Finalize()
{
}
