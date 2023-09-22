#include "CameraSystem.hpp"

#include "Input.hpp"
#include "Scenario.hpp"

#include "Component/Camera.hpp"
#include "Component/Transform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

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
        const auto mouseMovement = Input::GetCapturedMouseMovement() * m_Sensitivity;

        // Rotation
        transform.Rotation.x += glm::radians(mouseMovement.y);
        transform.Rotation.y += glm::radians(mouseMovement.x);

        // Clamp looking up and down to near +/- 90 degrees
        transform.Rotation.x = glm::clamp(transform.Rotation.x, glm::radians(-89.99f), glm::radians(89.99f));

        auto direction = glm::vec3(0.0f);
        direction.x = glm::cos(transform.Rotation.y) * glm::cos(transform.Rotation.x);
        direction.y = glm::sin(transform.Rotation.x);
        direction.z = glm::sin(transform.Rotation.y) * glm::cos(transform.Rotation.x);

        // Sets camera position to be at roughly 75% of the height of the entity
        const auto cameraHeight = transform.Position.y + (transform.Scale.y * 0.25f);
        const auto cameraPosition = glm::vec3(transform.Position.x, cameraHeight, transform.Position.z);

        auto& camera = e_Scenario.GetComponent<Camera>(entity);
        camera.ViewMatrix = glm::lookAt(cameraPosition, (cameraPosition + direction), glm::vec3(0.0f, 1.0f, 0.0f));
    }
}

void CameraSystem::Finalize()
{
}
