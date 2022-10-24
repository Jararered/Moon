#include "Renderer.hpp"

#include <glfw/glfw3.h>
#include <glad/gl.h>

Renderer::Renderer()
{
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Renderer::~Renderer()
{
    std::cout << "Renderer::~Renderer()\n";
}

void Renderer::Update(float dt)
{
    // New frame
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 0.0f, 1.0f, 0.0f);

    // Rendering happens here
    for (auto &camera : m_Cameras)
    {
        camera.Update(dt);
    }

    // Swap frames
    glfwSwapBuffers(glfwGetCurrentContext());
}

Camera& Renderer::CreateCamera()
{
    return m_Cameras.emplace_back();
}