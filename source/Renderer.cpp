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
            glUniformMatrix4fv(glGetUniformLocation(mesh.GetShader().GetID(), "u_ViewMatrix"), 1, GL_FALSE, &camera.GetViewMatrix()[0][0]);
            glUniformMatrix4fv(glGetUniformLocation(mesh.GetShader().GetID(), "u_ProjectionMatrix"), 1, GL_FALSE, &camera.GetProjectionMatrix()[0][0]);

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
    Geometry geometry;
    Shader shader;

    unsigned int &offset = geometry.Offset;
    int x = 0, y = 0, z = 0;

    geometry.Indices.insert(geometry.Indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
    geometry.Vertices.emplace_back(glm::vec3{x + 0.5f, y + 0.5f, z + 0.5f}, glm::vec3{1.0f, 0.0f, 0.0f});
    geometry.Vertices.emplace_back(glm::vec3{x + 0.5f, y - 0.5f, z + 0.5f}, glm::vec3{1.0f, 0.0f, 0.0f});
    geometry.Vertices.emplace_back(glm::vec3{x + 0.5f, y - 0.5f, z - 0.5f}, glm::vec3{1.0f, 0.0f, 0.0f});
    geometry.Vertices.emplace_back(glm::vec3{x + 0.5f, y + 0.5f, z - 0.5f}, glm::vec3{1.0f, 0.0f, 0.0f});
    offset += 4;
    geometry.Indices.insert(geometry.Indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
    geometry.Vertices.emplace_back(glm::vec3{x - 0.5f, y + 0.5f, z + 0.5f}, glm::vec3{1.0f, 0.0f, 0.0f});
    geometry.Vertices.emplace_back(glm::vec3{x - 0.5f, y + 0.5f, z - 0.5f}, glm::vec3{1.0f, 0.0f, 0.0f});
    geometry.Vertices.emplace_back(glm::vec3{x - 0.5f, y - 0.5f, z - 0.5f}, glm::vec3{1.0f, 0.0f, 0.0f});
    geometry.Vertices.emplace_back(glm::vec3{x - 0.5f, y - 0.5f, z + 0.5f}, glm::vec3{1.0f, 0.0f, 0.0f});
    offset += 4;
    geometry.Indices.insert(geometry.Indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
    geometry.Vertices.emplace_back(glm::vec3{x + 0.5f, y + 0.5f, z + 0.5f}, glm::vec3{0.0f, 1.0f, 0.0f});
    geometry.Vertices.emplace_back(glm::vec3{x + 0.5f, y + 0.5f, z - 0.5f}, glm::vec3{0.0f, 1.0f, 0.0f});
    geometry.Vertices.emplace_back(glm::vec3{x - 0.5f, y + 0.5f, z - 0.5f}, glm::vec3{0.0f, 1.0f, 0.0f});
    geometry.Vertices.emplace_back(glm::vec3{x - 0.5f, y + 0.5f, z + 0.5f}, glm::vec3{0.0f, 1.0f, 0.0f});
    offset += 4;
    geometry.Indices.insert(geometry.Indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
    geometry.Vertices.emplace_back(glm::vec3{x + 0.5f, y - 0.5f, z + 0.5f}, glm::vec3{0.0f, 1.0f, 0.0f});
    geometry.Vertices.emplace_back(glm::vec3{x - 0.5f, y - 0.5f, z + 0.5f}, glm::vec3{0.0f, 1.0f, 0.0f});
    geometry.Vertices.emplace_back(glm::vec3{x - 0.5f, y - 0.5f, z - 0.5f}, glm::vec3{0.0f, 1.0f, 0.0f});
    geometry.Vertices.emplace_back(glm::vec3{x + 0.5f, y - 0.5f, z - 0.5f}, glm::vec3{0.0f, 1.0f, 0.0f});
    offset += 4;
    geometry.Indices.insert(geometry.Indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
    geometry.Vertices.emplace_back(glm::vec3{x + 0.5f, y + 0.5f, z + 0.5f}, glm::vec3{0.0f, 0.0f, 1.0f});
    geometry.Vertices.emplace_back(glm::vec3{x - 0.5f, y + 0.5f, z + 0.5f}, glm::vec3{0.0f, 0.0f, 1.0f});
    geometry.Vertices.emplace_back(glm::vec3{x - 0.5f, y - 0.5f, z + 0.5f}, glm::vec3{0.0f, 0.0f, 1.0f});
    geometry.Vertices.emplace_back(glm::vec3{x + 0.5f, y - 0.5f, z + 0.5f}, glm::vec3{0.0f, 0.0f, 1.0f});
    offset += 4;
    geometry.Indices.insert(geometry.Indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
    geometry.Vertices.emplace_back(glm::vec3{x + 0.5f, y + 0.5f, z - 0.5f}, glm::vec3{0.0f, 0.0f, 1.0f});
    geometry.Vertices.emplace_back(glm::vec3{x + 0.5f, y - 0.5f, z - 0.5f}, glm::vec3{0.0f, 0.0f, 1.0f});
    geometry.Vertices.emplace_back(glm::vec3{x - 0.5f, y - 0.5f, z - 0.5f}, glm::vec3{0.0f, 0.0f, 1.0f});
    geometry.Vertices.emplace_back(glm::vec3{x - 0.5f, y + 0.5f, z - 0.5f}, glm::vec3{0.0f, 0.0f, 1.0f});
    offset += 4;

    shader.Compile("../source/render/shaders/BasicShader.vert", "../source/render/shaders/BasicShader.frag");

    Mesh &mesh = m_Meshes.emplace_back(geometry, shader);
    return mesh;
}