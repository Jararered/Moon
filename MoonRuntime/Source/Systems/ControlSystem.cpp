#include "ControlSystem.hpp"

#include "Input.hpp"
#include "Scenario.hpp"
#include "Signature.hpp"

#include "Component/Control.hpp"
#include "Component/Transform.hpp"

#include <glm/trigonometric.hpp>

extern Scenario e_Scenario;

void ControlSystem::Register()
{
    Signature signature;
    signature.set(e_Scenario.GetComponentType<Transform>());
    signature.set(e_Scenario.GetComponentType<Control>());
    e_Scenario.SetSystemSignature<ControlSystem>(signature);
}

void ControlSystem::Initialize()
{
}

void ControlSystem::Update(float dt)
{
    for (const auto& entity : m_Entities)
    {
        auto& transform = e_Scenario.GetComponent<Transform>(entity);

        auto direction = glm::vec3(0.0f);
        direction.x = glm::cos(transform.Rotation.y) * glm::cos(transform.Rotation.x);
        direction.y = glm::sin(transform.Rotation.x);
        direction.z = glm::sin(transform.Rotation.y) * glm::cos(transform.Rotation.x);

        // Normalize Direction vector and update Right vector
        direction = glm::normalize(direction);
        const auto right = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));
        const auto fowardXZ = glm::vec3(direction.x, 0.0f, direction.z);

        // WASD movement
        auto positionDelta = glm::vec3(0.0f);
        if (Input::IsKeyPressed(Key::W))
            positionDelta += fowardXZ;
        if (Input::IsKeyPressed(Key::S))
            positionDelta -= fowardXZ;
        if (Input::IsKeyPressed(Key::A))
            positionDelta -= right;
        if (Input::IsKeyPressed(Key::D))
            positionDelta += right;

        // Fixes diagonal directed movement to not be faster than along an axis.
        // Only happens when holding two buttons that are off axis from each other.
        if ((positionDelta.x != 0.0f) or (positionDelta.z != 0.0f))
            positionDelta = glm::normalize(positionDelta);

        // Still perform up/down movements after normalization.
        // Don't care about limiting speed along verticals.
        if (Input::IsKeyPressed(Key::Space))
            positionDelta += glm::vec3(0.0f, 1.0f, 0.0f);
        if (Input::IsKeyPressed(Key::LeftShift))
            positionDelta -= glm::vec3(0.0f, 1.0f, 0.0f);
        if (Input::IsKeyPressed(Key::LeftControl))
            positionDelta *= 10.0f;

        transform.Position += positionDelta * dt * 10.0f;
    }
}

void ControlSystem::Finalize()
{
}
