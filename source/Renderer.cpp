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

        for (auto &mesh : m_Meshes)
        {
            // Bind mesh that is being rendered
            mesh.Bind();

            // Update uniform data
            glUniformMatrix4fv(glGetUniformLocation(mesh.GetShader().GetID(), "u_ViewMatrix"), 1, GL_FALSE, &camera.GetViewMatrix()[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(mesh.GetShader().GetID(), "u_ProjectionMatrix"), 1, GL_FALSE, &camera.GetProjectionMatrix()[0][0]);

            // Finally draw everything
            glDrawElements(GL_TRIANGLES, mesh.GetGeometry().Indices.size(), GL_UNSIGNED_INT, (void *)0);
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
    int x = 0, y = 0, z = 0;

    glm::vec3 red = {1.0f, 0.0f, 0.0f};
    geometry.Indices.insert(geometry.Indices.end(), {0 + geometry.Offset, 1 + geometry.Offset, 2 + geometry.Offset, 2 + geometry.Offset, 3 + geometry.Offset, 0 + geometry.Offset});
    geometry.Vertices.emplace_back(glm::vec3{x + 0.5f, y - 0.5f, 0.0f}, red);
    geometry.Vertices.emplace_back(glm::vec3{x + 0.5f, y + 0.5f, 0.0f}, red);
    geometry.Vertices.emplace_back(glm::vec3{x - 0.5f, y + 0.5f, 0.0f}, red);
    geometry.Vertices.emplace_back(glm::vec3{x - 0.5f, y - 0.5f, 0.0f}, red);

    // Create shader for mesh
    shader.Compile("../source/render/shaders/BasicShader.vert", "../source/render/shaders/BasicShader.frag");

    // Add mesh to queue and retuen the entry
    return m_Meshes.emplace_back(geometry, shader);
}