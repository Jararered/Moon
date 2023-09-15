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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glCullFace(GL_BACK);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glfwSetWindowUserPointer(glfwGetCurrentContext(), this);
    glfwGetFramebufferSize(glfwGetCurrentContext(), &m_Width, &m_Height);

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

        renderer->m_Width = width;
        renderer->m_Height = height;
        renderer->ConfigureFramebuffer();

        const auto fov = glm::radians(90.0f);
        const auto aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        const auto projMatrix = glm::perspective(fov, aspectRatio, 0.1f, 1000.0f);
        auto& camera = g_Coordinator.GetComponent<Camera>(renderer->m_Camera);
        camera.ProjectionMatrix = projMatrix;
    };
    glfwSetFramebufferSizeCallback(glfwGetCurrentContext(), framebufferSizeCallback);

    ConfigureFramebuffer();

    m_ScreenShader = Shader("Shaders/PositionTexture.vert", "Shaders/PositionTexture.frag");
}

void RenderSystem::Update(float dt)
{
    PollDebugControls();

    // Bind Framebuffer and draw all objects to it
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

    // Unbind Framebuffer and draw quad
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Draw 2D Screen Quad
    glDisable(GL_DEPTH_TEST);
    glUseProgram(m_ScreenShader.ID);
    m_CurrentShader = m_ScreenShader.ID;
    glBindTexture(GL_TEXTURE_2D, m_TBO);
    m_CurrentTexture = m_TBO;
    m_ScreenMesh.Draw();

    glfwSwapBuffers(glfwGetCurrentContext());
}

void RenderSystem::Finalize()
{
}

void RenderSystem::ConfigureFramebuffer()
{
    // Delete previous buffers if they exist
    if (m_FBO != 0)
        glDeleteFramebuffers(1, &m_FBO);
    if (m_TBO != 0)
        glDeleteTextures(1, &m_TBO);
    if (m_RBO != 0)
        glDeleteRenderbuffers(1, &m_RBO);

    // Create framebuffer
    glGenFramebuffers(1, &m_FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

    // Create texturebuffer
    glGenTextures(1, &m_TBO);
    glBindTexture(GL_TEXTURE_2D, m_TBO);

    // Configure texturebuffer
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TBO, 0);

    // Create renderbuffer
    glGenRenderbuffers(1, &m_RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);

    // Configure renderbuffer
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

    // Check if the framebuffer was made successfully
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::println("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    std::println("FBO: {}, TBO: {}, RBO: {}", m_FBO, m_TBO, m_RBO);
}

void RenderSystem::PollDebugControls()
{
    // Do not fill polygons
    if (Input::IsKeyPressed(KEY_MINUS))
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        std::println("Wireframe enabled.");
    }

    // Fill polygons
    if (Input::IsKeyPressed(KEY_EQUAL))
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        std::println("Wireframe disabled.");
    }

    // Cull back faces
    if (Input::IsKeyPressed(KEY_MINUS) && Input::IsKeyPressed(KEY_RIGHT_SHIFT))
    {
        glEnable(GL_CULL_FACE);
    }

    // Do not cull back faces
    if (Input::IsKeyPressed(KEY_EQUAL) && Input::IsKeyPressed(KEY_RIGHT_SHIFT))
    {
        glDisable(GL_CULL_FACE);
    }
}
