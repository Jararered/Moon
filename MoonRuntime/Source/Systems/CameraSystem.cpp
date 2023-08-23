#include "CameraSystem.hpp"

#include "Coordinator.hpp"
#include "Input.hpp"
#include "System.hpp"

#include "Components/Camera.hpp"
#include "Components/Transform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

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

        glm::vec3 positionDelta = {0.0f, 0.0f, 0.0f};

        // Set Yaw and Pitch rotations based on mouse movement
        const glm::vec2 mouseMovement = Input::GetCapturedMouseMovement() / 5.0f;

        // Rotation
        transform.Rotation.x += glm::radians(mouseMovement.y);
        transform.Rotation.y += glm::radians(mouseMovement.x);
        transform.Rotation.z = 0.0f;

        if (transform.Rotation.x > glm::radians(90.0f))
            transform.Rotation.x = glm::radians(89.9f);
        if (transform.Rotation.x < glm::radians(-90.0f))
            transform.Rotation.x = glm::radians(-89.9f);

        glm::vec3 direction = {0.0f, 0.0f, 0.0f};
        direction.x = glm::cos(transform.Rotation.y) * glm::cos(transform.Rotation.x);
        direction.y = glm::sin(transform.Rotation.x);
        direction.z = glm::sin(transform.Rotation.y) * glm::cos(transform.Rotation.x);

        // Normalize Direction vector and update Right vector
        direction = glm::normalize(direction);
        const glm::vec3 right = glm::cross(direction, glm::vec3(0.0f, 1.0f, 0.0f));

        // Position
        // Basic movement processing
        const glm::vec3 fowardXZ = {direction.x, 0.0f, direction.z};

        // WASD movement
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

        transform.Position += positionDelta * dt * 10.0f;

        auto& cameraComponent = g_Coordinator.GetComponent<Camera>(entity);
        cameraComponent.ViewMatrix = glm::lookAt(transform.Position, (transform.Position + direction), glm::vec3(0.0f, 1.0f, 0.0f));

        // std::cout << transform.Position.x << ", " << transform.Position.y << ", " << transform.Position.z << "\n";
    }
}

void CameraSystem::Finalize()
{
}
