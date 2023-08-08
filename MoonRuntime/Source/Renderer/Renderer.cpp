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

    if (!p_Scenario)
        return;

    p_Scenario->Update(dt);
    Render();
}

void Renderer::Render()
{
    auto camera = p_Scenario->GetCamera();

    if (p_Scenario->GetSkybox())
    {
        p_Scenario->GetSkybox()->UpdatePosition();
        auto mesh = p_Scenario->GetSkybox()->GetMesh();
        auto shader = mesh->GetShader();
        shader.Bind();
        shader.SetMatrix("u_TranslationMatrix", mesh->GetTranslationMatrix());
        shader.SetMatrix("u_RotationMatrix", mesh->GetRotationMatrix());
        shader.SetMatrix("u_ViewMatrix", camera->GetViewMatrix());
        shader.SetMatrix("u_ProjectionMatrix", camera->GetProjectionMatrix());
        mesh->Draw();
    }

    for (auto& entity : p_Scenario->GetEntities())
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