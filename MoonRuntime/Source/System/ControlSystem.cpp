#include "ControlSystem.hpp"

#include "Core/Input.hpp"
#include "Core/Scenario.hpp"
#include "Core/Signature.hpp"

#include "Component/Controller.hpp"
#include "Component/RigidBody.hpp"
#include "Component/Transform.hpp"

#include <glm/trigonometric.hpp>
#include <imgui.h>

namespace Moon
{

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
        m_SpeedLimit = 2.5f;
        m_JumpMagnitude = 7.5f;
        m_WalkMagnitude = 5.0f;
        m_Name = "Control System";
    }

    void ControlSystem::Update(float)
    {
        for (const auto entity : m_UUIDs)
        {
            auto& transform = m_Scenario->GetComponent<Transform>(entity);
            auto& rigidBody = m_Scenario->GetComponent<RigidBody>(entity);
            auto speedLimit = m_SpeedLimit;

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
            velocity.x = m_WalkMagnitude * velocityDirection.x;
            velocity.y = m_JumpMagnitude * velocityDirection.y;
            velocity.z = m_WalkMagnitude * velocityDirection.z;
            rigidBody.Velocity += velocity;

            if (Input::IsKeyPressed(Key::LeftControl))
                speedLimit *= 1.5f;
            if (Input::IsKeyPressed(Key::LeftShift))
                speedLimit *= 0.5f;

            // Limit velocity in x,z directions
            auto xz = glm::vec3(rigidBody.Velocity.x, 0.0f, rigidBody.Velocity.z);
            if (glm::length(xz) > speedLimit and glm::length(xz) != 0.0f)
            {
                auto newxz = glm::normalize(xz) * speedLimit;
                rigidBody.Velocity.x = newxz.x;
                rigidBody.Velocity.z = newxz.z;
            }
        }
    }

    void ControlSystem::UpdateUI()
    {
        for (const auto entity : m_UUIDs)
        {
            auto& transform = m_Scenario->GetComponent<Transform>(entity);
            auto& rigidBody = m_Scenario->GetComponent<RigidBody>(entity);

            ImGui::LabelText("", "Rigid Body");
            ImGui::InputFloat3("Position", &transform.Position.x);
            ImGui::InputFloat3("Velocity", &rigidBody.Velocity.x);
            ImGui::InputFloat3("Acceleration", &rigidBody.Acceleration.x);

            ImGui::InputFloat("Jump Magnitude", &m_JumpMagnitude);
            ImGui::InputFloat("Walk Magnitude", &m_WalkMagnitude);
        }
    }

    void ControlSystem::Finalize()
    {
    }

}