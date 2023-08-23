#include "RenderSystem.hpp"

#include "System.hpp"

#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
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

    m_CameraEntity = g_Coordinator.CreateEntity();

    const glm::vec3 position = glm::vec3(0.0f, 0.0f, 100.0f);
    const glm::vec3 rotation = glm::vec3(0.0f, glm::radians(-90.0f), 0.0f); // Looking into the screen
    g_Coordinator.AddComponent(m_CameraEntity, Transform{.Position = position, .Rotation = rotation});

    const float fov = glm::radians(90.0f);
    const float aspectRatio = 16.0f / 9.0f;
    const glm::mat4 projMatrix = glm::perspective(fov, aspectRatio, 0.1f, 1000.0f);
    const glm::mat4 viewMatrix = glm::mat4(1.0f);
    g_Coordinator.AddComponent(m_CameraEntity, Camera{.ViewMatrix = viewMatrix, .ProjectionMatrix = projMatrix});
}

void RenderSystem::Update(float dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    PollDebugControls();

    const auto& camera = g_Coordinator.GetComponent<Camera>(m_CameraEntity);
    for (const auto& entity : m_Entities)
    {
        const auto& mesh = g_Coordinator.GetComponent<Mesh>(entity);
        const auto& shader = g_Coordinator.GetComponent<Shader>(entity);
        const auto& transform = g_Coordinator.GetComponent<Transform>(entity);
        const auto& texture = g_Coordinator.GetComponent<Texture>(entity);

        glUseProgram(shader.ID);
        glBindTexture(GL_TEXTURE_2D, texture.ID);

        glm::mat4 translationMatrix = glm::mat4(1.0f);
        translationMatrix = glm::translate(translationMatrix, transform.Position);

        glm::mat4 rotationMatrix = glm::mat4(1.0f);
        rotationMatrix = glm::rotate(rotationMatrix, transform.Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        rotationMatrix = glm::rotate(rotationMatrix, transform.Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        rotationMatrix = glm::rotate(rotationMatrix, transform.Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 scaleMatrix = glm::mat4(1.0f);
        scaleMatrix = glm::scale(scaleMatrix, transform.Scale);

        const glm::mat4 modelMatrix = translationMatrix * scaleMatrix * rotationMatrix;

        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "u_ModelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "u_ViewMatrix"), 1, GL_FALSE, (float*)&camera.ViewMatrix);
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "u_ProjectionMatrix"), 1, GL_FALSE, (float*)&camera.ProjectionMatrix);

        mesh.p_Mesh->Draw();
    }

    glfwSwapBuffers(glfwGetCurrentContext());
}

void RenderSystem::Finalize()
{
}

void RenderSystem::PollDebugControls()
{
    if (Input::IsKeyPressed(KEY_LEFT))
        EnableWireframes();
    if (Input::IsKeyPressed(KEY_RIGHT))
        DisableWireframes();
    if (Input::IsKeyPressed(KEY_UP))
        EnableBackCulling();
    if (Input::IsKeyPressed(KEY_DOWN))
        DisableBackCulling();
}
void RenderSystem::EnableWireframes()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
void RenderSystem::DisableWireframes()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
void RenderSystem::EnableBackCulling()
{
    glEnable(GL_CULL_FACE);
}
void RenderSystem::DisableBackCulling()
{
    glDisable(GL_CULL_FACE);
}
