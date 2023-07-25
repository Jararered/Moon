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
    // New frame
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rendering happens here
    for (auto& camera : m_Cameras)
    {
        camera->Update(dt);

        for (auto& mesh : m_Meshes)
        {
            mesh->Bind();

            // Update any time-related variables for the mesh
            mesh->Update(dt);

            // Draw the mesh
            mesh->Draw(camera);

            mesh->Unbind();
        }
    }

    // Swap frames
    glfwSwapBuffers(glfwGetCurrentContext());
}

Camera* Renderer::Create2DCamera()
{
    Camera* camera = new Camera2D();
    return m_Cameras.emplace_back(camera);
}

Camera* Renderer::Create3DCamera()
{
    Camera* camera = new Camera3D();
    return m_Cameras.emplace_back(camera);
}

void Renderer::AddMesh(Mesh* mesh)
{
    m_Meshes.push_back(mesh);
}