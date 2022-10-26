#include "Renderer.hpp"

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
    std::cout << "Renderer::~Renderer()\n";
}

void Renderer::Update(float dt)
{
    // New frame
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rendering happens here
    for (auto &camera : m_Cameras)
    {
        camera.Update(dt);

        for (auto &mesh : m_Meshes)
        {
            mesh.Bind();

            // Update any time-related variables for the mesh
            mesh.Update(dt);

            // Draw the mesh
            mesh.Draw(camera);

            mesh.Unbind();
        }
    }

    // Swap frames
    glfwSwapBuffers(glfwGetCurrentContext());
}

Camera &Renderer::CreateCamera()
{
    return m_Cameras.emplace_back();
}

Mesh &Renderer::CreateTestMesh()
{
    // Create blank mesh components
    Geometry geometry;
    Shader shader;

    // Position of center of square
    geometry.Indices.insert(geometry.Indices.end(), {0, 1, 2, 2, 3, 0});
    geometry.Vertices.emplace_back(glm::vec3{5.0f, -0.5f, -0.5f});
    geometry.Vertices.emplace_back(glm::vec3{5.0f, -0.5f, +0.5f});
    geometry.Vertices.emplace_back(glm::vec3{5.0f, +0.5f, -0.5f});
    geometry.Vertices.emplace_back(glm::vec3{5.0f, +0.5f, +0.5f});

    // Create shader for mesh
    shader.Compile("../source/render/shaders/Position.vert", "../source/render/shaders/colors/Red.frag");

    // Add mesh to queue and retuen the entry
    Mesh &mesh = m_Meshes.emplace_back(geometry, shader);
    return mesh;
}