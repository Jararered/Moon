#pragma once

#include <Moon.hpp>

namespace ExampleMesh
{
    Mesh* Square(glm::vec2 origin = glm::vec2(0.0f, 0.0f), float size = 0.0f)
    {
        // Create blank mesh components
        Geometry geometry;
        Shader shader;

        // Position of center of square
        geometry.Indices.insert(geometry.Indices.end(), { 0, 1, 2, 2, 3, 0 });
        geometry.Vertices.emplace_back(glm::vec3{ origin.x - (size / 2), origin.y - (size / 2), 0.0f });
        geometry.Vertices.emplace_back(glm::vec3{ origin.x - (size / 2), origin.y + (size / 2), 0.0f });
        geometry.Vertices.emplace_back(glm::vec3{ origin.x + (size / 2), origin.y + (size / 2), 0.0f });
        geometry.Vertices.emplace_back(glm::vec3{ origin.x + (size / 2), origin.y - (size / 2), 0.0f });

        // Create shader for mesh
        std::string cwd = Engine::CurrentDirectory();
        std::string vertFile = std::string("Shaders/Position.vert");
        std::string fragFile = std::string("Shaders/Colors/Red.frag");
        shader.Compile(vertFile, fragFile);

        // Add mesh to queue and return the entry
        Mesh* mesh = new Mesh(geometry, shader);
        return mesh;
    }
}