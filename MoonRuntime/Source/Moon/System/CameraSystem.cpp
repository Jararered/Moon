#include "CameraSystem.hpp"

#include "Components.hpp"
#include "Input.hpp"

#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

using namespace Moon;

void CameraSystem::Register(std::shared_ptr<Scenario> scenario)
{
    m_Scenario = scenario;

    Signature signature;
    signature.set(m_Scenario->GetComponentType<Transform>());
    signature.set(m_Scenario->GetComponentType<Camera>());
    m_Scenario->SetSystemSignature<CameraSystem>(signature);
}

void CameraSystem::Initialize()
{
}

void CameraSystem::Update(float)
{
    for (const auto entity : m_Entities)
    {
        auto& transform = m_Scenario->GetComponent<Transform>(entity);
        auto& camera = m_Scenario->GetComponent<Camera>(entity);

        // Set Yaw and Pitch rotations based on mouse movement
        const auto mouseMovement = Input::GetCapturedMouseMovement() * m_Sensitivity;

        // Rotation
        transform.Rotation.x += glm::radians(mouseMovement.y);
        transform.Rotation.y += glm::radians(mouseMovement.x);

        // Clamp looking up and down to near +/- 90 degrees
        transform.Rotation.x = glm::clamp(transform.Rotation.x, glm::radians(-89.99f), glm::radians(89.99f));

        // rotation in radians
        while (transform.Rotation.y > glm::radians(360.0f))
            transform.Rotation.y -= glm::radians(360.0f);
        while (transform.Rotation.y < glm::radians(-360.0f))
            transform.Rotation.y += glm::radians(360.0f);

        auto direction = glm::vec3(0.0f);
        direction.x = glm::cos(transform.Rotation.y) * glm::cos(transform.Rotation.x);
        direction.y = glm::sin(transform.Rotation.x);
        direction.z = glm::sin(transform.Rotation.y) * glm::cos(transform.Rotation.x);

        // Sets camera position to be at roughly 75% of the height of the entity
        const auto cameraHeight = transform.Position.y + (transform.Scale.y * 0.25f);
        const auto cameraPosition = glm::vec3(transform.Position.x, cameraHeight, transform.Position.z);

        camera.ViewMatrix = glm::lookAt(cameraPosition, (cameraPosition + direction), glm::vec3(0.0f, 1.0f, 0.0f));
    }
}

void CameraSystem::Finalize()
{
}

void CameraSystem::UpdatePerspective(UUID entity)
{
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);

    auto& camera = m_Scenario->GetComponent<Camera>(entity);
    camera.ProjectionMatrix = glm::perspective(glm::radians(camera.FOV), static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);
}
