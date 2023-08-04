#include "Renderer.hpp"

#include <glad/gl.h>
#include <glfw/glfw3.h>

#include "Camera2D.hpp"
#include "Camera3D.hpp"

Renderer::Renderer()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Renderer::Update(float dt)
{
    PollDebugControls();

    if (m_Scenarios.empty())
        return;

    for (auto scenario : m_Scenarios)
    {
        scenario->Update(dt);
        Render(scenario);
    }
}

void Renderer::Render(Scenario* scenario)
{
    auto camera = scenario->GetCamera();

    if (camera->GetSkybox())
    {
        camera->GetSkybox()->UpdatePosition();
        auto mesh = camera->GetSkybox()->GetMesh();
        auto shader = mesh->GetShader();
        shader.Bind();
        shader.SetMatrix("u_TranslationMatrix", mesh->GetTranslationMatrix());
        shader.SetMatrix("u_RotationMatrix", mesh->GetRotationMatrix());
        shader.SetMatrix("u_ViewMatrix", camera->GetViewMatrix());
        shader.SetMatrix("u_ProjectionMatrix", camera->GetProjectionMatrix());
        mesh->Draw();
    }

    for (auto& entity : scenario->GetEntities())
    {
        auto mesh = entity->GetMesh();
        auto& shader = mesh->GetShader();

        shader.Bind();

        shader.SetMatrix("u_TranslationMatrix", mesh->GetTranslationMatrix());
        shader.SetMatrix("u_RotationMatrix", mesh->GetRotationMatrix());

        shader.SetMatrix("u_ViewMatrix", camera->GetViewMatrix());
        shader.SetMatrix("u_ProjectionMatrix", camera->GetProjectionMatrix());

        mesh->Draw();
    }
}

void Renderer::PollDebugControls()
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