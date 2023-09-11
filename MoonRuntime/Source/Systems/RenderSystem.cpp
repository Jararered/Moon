#include "RenderSystem.hpp"

#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/trigonometric.hpp>

#include "Coordinator.hpp"
#include "Input.hpp"

#include "Components/Camera.hpp"
#include "Components/Mesh.hpp"
#include "Components/Shader.hpp"
#include "Components/Texture.hpp"
#include "Components/Transform.hpp"

extern Coordinator g_Coordinator;

void RenderSystem::Register()
{
    Signature signature;
    signature.set(g_Coordinator.GetComponentType<Mesh>());
    signature.set(g_Coordinator.GetComponentType<Transform>());
    signature.set(g_Coordinator.GetComponentType<Shader>());
    signature.set(g_Coordinator.GetComponentType<Texture>());
    g_Coordinator.SetSystemSignature<RenderSystem>(signature);
}

void RenderSystem::Initialize()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glfwSetWindowUserPointer(glfwGetCurrentContext(), this);

    m_Camera = g_Coordinator.CreateEntity();

    const auto position = glm::vec3(0.0f, 0.0f, 0.0f);
    const auto rotation = glm::vec3(0.0f, glm::radians(-90.0f), 0.0f); // Looking into the screen
    g_Coordinator.AddComponent(m_Camera, Transform{.Position = position, .Rotation = rotation});

    const auto fov = glm::radians(90.0f);
    const auto aspectRatio = 16.0f / 9.0f;
    const auto projMatrix = glm::perspective(fov, aspectRatio, 0.1f, 1000.0f);
    const auto viewMatrix = glm::mat4(1.0f);
    g_Coordinator.AddComponent(m_Camera, Camera{.ViewMatrix = viewMatrix, .ProjectionMatrix = projMatrix});

    auto framebufferSizeCallback = [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);

        const auto renderer = static_cast<RenderSystem*>(glfwGetWindowUserPointer(glfwGetCurrentContext()));

        const auto fov = glm::radians(90.0f);
        const auto aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        const auto projMatrix = glm::perspective(fov, aspectRatio, 0.1f, 1000.0f);
        auto& camera = g_Coordinator.GetComponent<Camera>(renderer->m_Camera);
        camera.ProjectionMatrix = projMatrix;
    };
    glfwSetFramebufferSizeCallback(glfwGetCurrentContext(), framebufferSizeCallback);
}

void RenderSystem::Update(float dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    PollDebugControls();

    const auto& camera = g_Coordinator.GetComponent<Camera>(m_Camera);
    for (const auto& entity : m_Entities)
    {
        const auto& shader = g_Coordinator.GetComponent<Shader>(entity);
        if (m_CurrentShader != shader.ID)
        {
            glUseProgram(shader.ID);
            m_CurrentShader = shader.ID;
        }

        const auto& texture = g_Coordinator.GetComponent<Texture>(entity);
        if (m_CurrentTexture != texture.ID)
        {
            glBindTexture(GL_TEXTURE_2D, texture.ID);
            m_CurrentTexture = texture.ID;
        }

        const auto& transform = g_Coordinator.GetComponent<Transform>(entity);
        const auto translationMatrix = glm::translate(glm::mat4(1.0f), transform.Position);
        const auto scaleMatrix = glm::scale(glm::mat4(1.0f), transform.Scale);
        const auto rotationMatrix = glm::eulerAngleXYZ(transform.Rotation.x, transform.Rotation.y, transform.Rotation.z);
        const auto modelMatrix = translationMatrix * scaleMatrix * rotationMatrix;

        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "u_ModelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "u_ViewMatrix"), 1, GL_FALSE, (float*)&camera.ViewMatrix);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "u_ProjectionMatrix"), 1, GL_FALSE, (float*)&camera.ProjectionMatrix);

        const auto& mesh = g_Coordinator.GetComponent<Mesh>(entity);
        mesh->Draw();
    }

    glfwSwapBuffers(glfwGetCurrentContext());
}

void RenderSystem::Finalize()
{
}

void RenderSystem::PollDebugControls()
{
    // Do not fill polygons
    if (Input::IsKeyPressed(KEY_MINUS))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Fill polygons
    if (Input::IsKeyPressed(KEY_EQUAL))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Cull back faces
    if (Input::IsKeyPressed(KEY_MINUS) && Input::IsKeyPressed(KEY_RIGHT_SHIFT))
        glEnable(GL_CULL_FACE);

    // Do not cull back faces
    if (Input::IsKeyPressed(KEY_EQUAL) && Input::IsKeyPressed(KEY_RIGHT_SHIFT))
        glDisable(GL_CULL_FACE);
}
