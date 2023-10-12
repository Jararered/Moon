#include "RenderSystem.hpp"

#include "Core/Input.hpp"
#include "Core/Scenario.hpp"

#include "Components/Camera.hpp"
#include "Components/Control.hpp"
#include "Components/Mesh.hpp"
#include "Components/RigidBody.hpp"
#include "Components/Shader.hpp"
#include "Components/Texture.hpp"
#include "Components/Transform.hpp"

#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/trigonometric.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void RenderSystem::Register(std::shared_ptr<Scenario> scenario)
{
    m_Scenario = scenario;

    Signature signature;
    signature.set(m_Scenario->GetComponentType<Mesh>());
    signature.set(m_Scenario->GetComponentType<Transform>());
    signature.set(m_Scenario->GetComponentType<Shader>());
    signature.set(m_Scenario->GetComponentType<Texture>());
    m_Scenario->SetSystemSignature<RenderSystem>(signature);
}

void RenderSystem::Initialize()
{
    m_Name = "Render System";
    m_NearClip = 0.1f;
    m_FarClip = 1000.0f;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.15f, 0.15f, 0.15f, 0.0f);
    glCullFace(GL_BACK);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glfwGetFramebufferSize(glfwGetCurrentContext(), &m_Width, &m_Height);
    m_Framebuffer.Create(m_Width, m_Height);

    m_Camera = m_Scenario->CreateEntity();

    const auto position = glm::vec3(0.0f);
    const auto rotation = glm::vec3(0.0f, glm::radians(-90.0f), 0.0f); // Looking into the screen
    const auto scale = glm::vec3(0.5f, 2.0f, 0.5f);
    const auto fov = 85.0f;
    const auto aspectRatio = 16.0f / 9.0f;
    const auto projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, m_NearClip, m_FarClip);
    const auto viewMatrix = glm::mat4(1.0f);
    m_Scenario->AddComponent<Transform>(m_Camera, Transform{.Position = position, .Rotation = rotation, .Scale = scale});
    m_Scenario->AddComponent<Camera>(m_Camera, Camera{.ViewMatrix = viewMatrix, .ProjectionMatrix = projectionMatrix, .FOV = fov});

    // Adding a rigid body to the camera so that it cannot pass through other objects
    m_Scenario->AddComponent<RigidBody>(m_Camera, RigidBody{.Velocity = {0.0f, 0.0f, 0.0f}, .Acceleration = {0.0f, 0.0f, 0.0f}, .Mass = 1.0f});

    m_Scenario->AddComponent<Control>(m_Camera);

    ConfigureCallbacks();
}

void RenderSystem::Update(float dt)
{
    m_Framebuffer.Bind();

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, m_PolygonMode);

    const auto camera = m_Scenario->GetComponent<Camera>(m_Camera);
    for (const auto& entity : m_Entities)
    {
        const auto& shader = m_Scenario->GetComponent<Shader>(entity);
        glUseProgram(shader.ID);

        const auto& texture = m_Scenario->GetComponent<Texture>(entity);
        glBindTexture(GL_TEXTURE_2D, texture.ID);

        const auto& transform = m_Scenario->GetComponent<Transform>(entity);
        const auto translationMatrix = glm::translate(glm::mat4(1.0f), transform.Position);
        const auto scaleMatrix = glm::scale(glm::mat4(1.0f), transform.Scale);
        const auto rotationMatrix = glm::eulerAngleXYZ(transform.Rotation.x, transform.Rotation.y, transform.Rotation.z);
        const auto modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "u_ModelMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "u_ViewMatrix"), 1, GL_FALSE, &camera.ViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "u_ProjectionMatrix"), 1, GL_FALSE, &camera.ProjectionMatrix[0][0]);

        m_Scenario->GetComponent<Mesh>(entity)->Draw();
    }

    m_Framebuffer.Unbind();
    m_Framebuffer.Draw();
}

void RenderSystem::UpdateUI()
{
    if (ImGui::InputFloat("Near", &m_NearClip))
        ConfigureFramebuffer(m_Width, m_Height);
    if (ImGui::InputFloat("Far", &m_FarClip))
        ConfigureFramebuffer(m_Width, m_Height);
    if (ImGui::Button("Enable Wireframe"))
        m_PolygonMode = GL_LINE;
    ImGui::SameLine();
    if (ImGui::Button("Disable Wireframe"))
        m_PolygonMode = GL_FILL;
}

void RenderSystem::Finalize()
{
}

void RenderSystem::ConfigureFramebuffer(int width, int height)
{
    glViewport(0, 0, width, height);

    m_Width = width;
    m_Height = height;

    m_Framebuffer.Delete();
    m_Framebuffer.Create(width, height);

    auto& camera = m_Scenario->GetComponent<Camera>(m_Camera);
    camera.ProjectionMatrix = glm::perspective(glm::radians(camera.FOV), static_cast<float>(width) / static_cast<float>(height), m_NearClip, m_FarClip);
}

void RenderSystem::ConfigureCallbacks()
{
    glfwSetWindowUserPointer(glfwGetCurrentContext(), this);

    const auto framebufferSizeCallback = [](GLFWwindow* window, int width, int height)
    {
        const auto renderer = static_cast<RenderSystem*>(glfwGetWindowUserPointer(window));
        renderer->ConfigureFramebuffer(width, height);
    };
    glfwSetFramebufferSizeCallback(glfwGetCurrentContext(), framebufferSizeCallback);
}