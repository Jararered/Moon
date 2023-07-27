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
}

Renderer::~Renderer()
{
}

void Renderer::ClearBuffer()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
    auto environment = scenario->GetEnvironment();

    for (auto entity : scenario->GetEntities())
    {
        auto model = entity->GetMesh();
        auto shader = model->GetShader();

        model->Bind();

        shader.SetMatrix("u_TranslationMatrix", model->GetTranslationMatrix());
        shader.SetMatrix("u_RotationMatrix", model->GetRotationMatrix());
        shader.SetMatrix("u_ViewMatrix", camera->GetViewMatrix());
        shader.SetMatrix("u_ProjectionMatrix", camera->GetProjectionMatrix());

        model->Draw();
        model->Unbind();
    }
}