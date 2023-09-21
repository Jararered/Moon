#include "CameraSystem.hpp"

#include "Input.hpp"
#include "Scenario.hpp"

#include "Component/Camera.hpp"
#include "Component/Transform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>
#include <print>

extern Scenario e_Scenario;

void CameraSystem::Register()
{
    Signature signature;
    signature.set(e_Scenario.GetComponentType<Transform>());
    signature.set(e_Scenario.GetComponentType<Camera>());
    e_Scenario.SetSystemSignature<CameraSystem>(signature);
}

void CameraSystem::Initialize()
{
}

void CameraSystem::Update(float dt)
{
    for (const auto& entity : m_Entities)
    {
        auto& transform = e_Scenario.GetComponent<Transform>(entity);
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

        auto& camera = e_Scenario.GetComponent<Camera>(entity);
        const auto viewMatrix = glm::lookAt(transform.Position, (transform.Position + direction), glm::vec3(0.0f, 1.0f, 0.0f));
        camera.ViewMatrix = viewMatrix;
    }
}

void CameraSystem::Finalize()
{
}
