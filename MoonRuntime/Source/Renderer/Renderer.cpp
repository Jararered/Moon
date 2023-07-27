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

void Renderer::Reset()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Update(float dt)
{
    Reset();

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
    auto id = camera->GetShader()->GetID();
    camera->GetShader()->Bind();
    glUniformMatrix4fv(glGetUniformLocation(id, "u_ProjectionMatrix"), 1, GL_FALSE, &camera->GetProjectionMatrix()[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(id, "u_ViewMatrix"), 1, GL_FALSE, &camera->GetViewMatrix()[0][0]);

    for (auto entity : scenario->GetEntities())
    {
        auto model = entity->GetModel();

        model->Bind();

        glUniformMatrix4fv(glGetUniformLocation(id, "u_TranslationMatrix"), 1, GL_FALSE, &model->GetTranslationMatrix()[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(id, "u_RotationMatrix"), 1, GL_FALSE, &model->GetRotationMatrix()[0][0]);

        model->Draw();
        model->Unbind();
    }
}