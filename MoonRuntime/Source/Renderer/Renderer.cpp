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
}

Renderer::~Renderer()
{
}

void Renderer::Update(float dt)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto camera : m_Cameras)
    {
        camera->Update(dt);
        camera->GetShader()->Bind();

        glUniformMatrix4fv(glGetUniformLocation(camera->GetShader()->ID, "u_ViewMatrix"), 1, GL_FALSE, &camera->GetViewMatrix()[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(camera->GetShader()->ID, "u_ProjectionMatrix"), 1, GL_FALSE, &camera->GetProjectionMatrix()[0][0]);

        for (auto mesh : m_Meshes)
        {
            mesh->Bind();
            mesh->Update(dt);
            mesh->Draw();
            mesh->Unbind();
        }
    }

    glfwSwapBuffers(glfwGetCurrentContext());
}

void Renderer::AddMesh(Mesh* mesh)
{
    m_Meshes.push_back(mesh);
}

void Renderer::AddCamera(Camera* camera)
{
    m_Cameras.push_back(camera);
}