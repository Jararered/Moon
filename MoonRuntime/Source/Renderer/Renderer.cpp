#include "Renderer.hpp"

#include "Camera2D.hpp"
#include "Camera3D.hpp"

#include <glfw/glfw3.h>
#include <glad/gl.h>

Renderer::Renderer()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Renderer::~Renderer()
{
}

void Renderer::ClearBuffer()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Update(float dt)
{
    ClearBuffer();

    if (m_Scenarios.empty())
        return;

    for (auto scenario : m_Scenarios)
    {
        scenario->Update(dt);
        Render(scenario);
    }

    glfwSwapBuffers(glfwGetCurrentContext());
}

void Renderer::Render(Scenario* scenario)
{
    auto camera = scenario->GetCamera();

    if (camera->GetSkybox())
    {
        camera->GetSkybox()->Update(0.0f);
        auto mesh = camera->GetSkybox()->GetMesh();
        auto shader = mesh->GetShader();
        shader.Bind();
        shader.SetMatrix("u_TranslationMatrix", mesh->GetTranslationMatrix());
        shader.SetMatrix("u_RotationMatrix", mesh->GetRotationMatrix());
        shader.SetMatrix("u_ViewMatrix", camera->GetViewMatrix());
        shader.SetMatrix("u_ProjectionMatrix", camera->GetProjectionMatrix());
        mesh->Draw();
    }

    for (auto entity : scenario->GetEntities())
    {
        auto mesh = entity->GetMesh();
        auto shader = mesh->GetShader();

        shader.Bind();

        shader.SetMatrix("u_TranslationMatrix", mesh->GetTranslationMatrix());
        shader.SetMatrix("u_RotationMatrix", mesh->GetRotationMatrix());
        shader.SetMatrix("u_ViewMatrix", camera->GetViewMatrix());
        shader.SetMatrix("u_ProjectionMatrix", camera->GetProjectionMatrix());

        mesh->Draw();
    }
}