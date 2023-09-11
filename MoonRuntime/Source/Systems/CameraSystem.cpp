#include "CameraSystem.hpp"

#include "Coordinator.hpp"
#include "Input.hpp"

#include "Components/Camera.hpp"
#include "Components/Transform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <print>

extern Coordinator g_Coordinator;

void CameraSystem::Register()
{
    Signature signature;
    signature.set(g_Coordinator.GetComponentType<Transform>());
    signature.set(g_Coordinator.GetComponentType<Camera>());
    g_Coordinator.SetSystemSignature<CameraSystem>(signature);
}

void CameraSystem::Initialize()
{
}

void CameraSystem::Update(float dt)
{
    for (const auto& entity : m_Entities)
    {
        auto& transform = g_Coordinator.GetComponent<Transform>(entity);
        // Set Yaw and Pitch rotations based on mouse movement
        const auto mouseMovement = Input::GetCapturedMouseMovement() / 5.0f;

        // Rotation
        transform.Rotation.x += glm::radians(mouseMovement.y);
        transform.Rotation.y += glm::radians(mouseMovement.x);
        transform.Rotation.z = 0.0f;

        if (transform.Rotation.x > glm::radians(90.0f))
            transform.Rotation.x = glm::radians(89.9f);
        if (transform.Rotation.x < glm::radians(-90.0f))
            transform.Rotation.x = glm::radians(-89.9f);

        auto direction = glm::vec3(0.0f);
        direction.x = glm::cos(transform.Rotation.y) * glm::cos(transform.Rotation.x);
        direction.y = glm::sin(transform.Rotation.x);
        direction.z = glm::sin(transform.Rotation.y) * glm::cos(transform.Rotation.x);

        // Normalize Direction vector and update Right vector
        direction = glm::normalize(direction);
        const auto right = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));

        // Position
        // Basic movement processing
        const auto fowardXZ = glm::vec3(direction.x, 0.0f, direction.z);

        // WASD movement
        auto positionDelta = glm::vec3(0.0f);
        if (Input::IsKeyPressed(KEY_W))
            positionDelta += fowardXZ;
        if (Input::IsKeyPressed(KEY_S))
            positionDelta -= fowardXZ;
        if (Input::IsKeyPressed(KEY_A))
            positionDelta -= right;
        if (Input::IsKeyPressed(KEY_D))
            positionDelta += right;

        // Fixes diagonal directed movement to not be faster than along an axis.
        // Only happens when holding two buttons that are off axis from each other.
        if ((positionDelta.x != 0.0f) || (positionDelta.z != 0.0f))
            positionDelta = glm::normalize(positionDelta);

        // Still perform up/down movements after normalization.
        // Don't care about limiting speed along verticals.
        if (Input::IsKeyPressed(KEY_SPACE))
            positionDelta += glm::vec3(0.0f, 1.0f, 0.0f);
        if (Input::IsKeyPressed(KEY_LEFT_SHIFT))
            positionDelta -= glm::vec3(0.0f, 1.0f, 0.0f);
        if (Input::IsKeyPressed(KEY_LEFT_CONTROL))
            positionDelta *= 10.0f;

        transform.Position += positionDelta * dt * 10.0f;

        auto& camera = g_Coordinator.GetComponent<Camera>(entity);
        camera.ViewMatrix = glm::lookAt(transform.Position, (transform.Position + direction), glm::vec3(0.0f, 1.0f, 0.0f));
    }
}

void CameraSystem::Finalize()
{
}
