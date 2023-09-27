#include "RenderSystem.hpp"

#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/trigonometric.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Input.hpp"
#include "Scenario.hpp"

#include "Component/Camera.hpp"
#include "Component/Control.hpp"
#include "Component/Mesh.hpp"
#include "Component/RigidBody.hpp"
#include "Component/Shader.hpp"
#include "Component/Texture.hpp"
#include "Component/Transform.hpp"

extern Scenario e_Scenario;

void RenderSystem::Register()
{
    Signature signature;
    signature.set(e_Scenario.GetComponentType<Mesh>());
    signature.set(e_Scenario.GetComponentType<Transform>());
    signature.set(e_Scenario.GetComponentType<Shader>());
    signature.set(e_Scenario.GetComponentType<Texture>());
    e_Scenario.SetSystemSignature<RenderSystem>(signature);
}

void RenderSystem::Initialize()
{
    m_Name = "Render System";
    m_NearClip = 0.1f;
    m_FarClip = 1000.0f;

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glCullFace(GL_BACK);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glfwSetWindowUserPointer(glfwGetCurrentContext(), this);
    glfwGetFramebufferSize(glfwGetCurrentContext(), &m_Width, &m_Height);
    m_Framebuffer.Create(m_Width, m_Height);

    m_Camera = e_Scenario.CreateEntity();

    const auto position = glm::vec3(0.0f, 10.0f, 0.0f);
    const auto rotation = glm::vec3(0.0f, glm::radians(-90.0f), 0.0f); // Looking into the screen
    const auto scale = glm::vec3(0.5f, 2.0f, 0.5f);
    e_Scenario.AddComponent<Transform>(m_Camera, Transform{.Position = position, .Rotation = rotation, .Scale = scale});

    const auto fov = 85.0f;
    const auto aspectRatio = 16.0f / 9.0f;
    const auto projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, m_NearClip, m_FarClip);
    const auto viewMatrix = glm::mat4(1.0f);
    e_Scenario.AddComponent<Camera>(m_Camera, Camera{.ViewMatrix = viewMatrix, .ProjectionMatrix = projectionMatrix, .FOV = fov});

    // Adding a rigid body to the camera so that it cannot pass through other objects
    e_Scenario.AddComponent<RigidBody>(m_Camera, RigidBody{.Velocity = {0.0f, 0.0f, 0.0f}, .Acceleration = {0.0f, 0.0f, 0.0f}, .Mass = 1.0f});

    e_Scenario.AddComponent<Control>(m_Camera);

    const auto framebufferSizeCallback = [](GLFWwindow* window, int width, int height)
    {
        const auto renderer = static_cast<RenderSystem*>(glfwGetWindowUserPointer(window));
        renderer->CreateFramebuffer(width, height);
    };
    glfwSetFramebufferSizeCallback(glfwGetCurrentContext(), framebufferSizeCallback);
}

void RenderSystem::Update(float dt)
{
    m_Framebuffer.Bind();

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, m_PolygonMode);

    PollDebugControls();

    const auto camera = e_Scenario.GetComponent<Camera>(m_Camera);
    for (const auto& entity : m_Entities)
    {
        const auto& shader = e_Scenario.GetComponent<Shader>(entity);
        glUseProgram(shader.ID);

        const auto& texture = e_Scenario.GetComponent<Texture>(entity);
        glBindTexture(GL_TEXTURE_2D, texture.ID);

        const auto& transform = e_Scenario.GetComponent<Transform>(entity);
        const auto translationMatrix = glm::translate(glm::mat4(1.0f), transform.Position);
        const auto scaleMatrix = glm::scale(glm::mat4(1.0f), transform.Scale);
        const auto rotationMatrix = glm::eulerAngleXYZ(transform.Rotation.x, transform.Rotation.y, transform.Rotation.z);
        const auto modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "u_ModelMatrix"), 1, GL_FALSE, &modelMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "u_ViewMatrix"), 1, GL_FALSE, &camera.ViewMatrix[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "u_ProjectionMatrix"), 1, GL_FALSE, &camera.ProjectionMatrix[0][0]);

        e_Scenario.GetComponent<Mesh>(entity)->Draw();
    }

    m_Framebuffer.Unbind();
    m_Framebuffer.Draw();
}

void RenderSystem::UpdateUI()
{
    if (ImGui::InputFloat("Near", &m_NearClip))
        CreateFramebuffer(m_Width, m_Height);
    ImGui::SameLine();
    if (ImGui::InputFloat("Far", &m_FarClip))
        CreateFramebuffer(m_Width, m_Height);
    if (ImGui::Button("Enable Wireframe"))
        m_PolygonMode = GL_LINE;
    ImGui::SameLine();
    if (ImGui::Button("Disable Wireframe"))
        m_PolygonMode = GL_FILL;
}

void RenderSystem::Finalize()
{
}

void RenderSystem::PollDebugControls()
{
    // Do not fill polygons
    if (Input::IsKeyPressed(Key::Minus))
        m_PolygonMode = GL_LINE;

    // Fill polygons
    if (Input::IsKeyPressed(Key::Equal))
        m_PolygonMode = GL_FILL;
}

void RenderSystem::CreateFramebuffer(int width, int height)
{
    glViewport(0, 0, width, height);

    m_Width = width;
    m_Height = height;

    m_Framebuffer.Delete();
    m_Framebuffer.Create(width, height);

    auto& camera = e_Scenario.GetComponent<Camera>(m_Camera);
    camera.ProjectionMatrix = glm::perspective(glm::radians(camera.FOV), static_cast<float>(width) / static_cast<float>(height), m_NearClip, m_FarClip);
}
