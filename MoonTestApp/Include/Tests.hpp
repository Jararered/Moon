#pragma once

#include <Moon.hpp>

namespace ExampleMesh
{
    Mesh* Square()
    {
        // Create blank mesh components
        Geometry geometry;
        Shader shader;

        // Position of center of square
        geometry.Indices.insert(geometry.Indices.end(), { 0, 1, 2, 2, 3, 0 });
        geometry.Vertices.emplace_back(glm::vec3{ -0.5f, -0.5f, 0.0f });
        geometry.Vertices.emplace_back(glm::vec3{ -0.5f, +0.5f, 0.0f });
        geometry.Vertices.emplace_back(glm::vec3{ +0.5f, +0.5f, 0.0f });
        geometry.Vertices.emplace_back(glm::vec3{ +0.5f, -0.5f, 0.0f });

        // Create shader for mesh
        shader.Compile("Shaders/Position.vert", "Shaders/Colors/Red.frag");

        // Add mesh to queue and return the entry
        Mesh* mesh = new Mesh(geometry, shader);
        return mesh;
    }
}