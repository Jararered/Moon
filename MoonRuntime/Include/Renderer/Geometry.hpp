#pragma once

#include <glm/vec3.hpp>
#include <vector>

struct Vertex
{
    Vertex(glm::vec3 position);
    Vertex(glm::vec3 position, glm::vec3 color);
    Vertex(glm::vec3 position, glm::vec3 color, glm::vec3 normal);

    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec3 Normal;
};

struct Geometry
{
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    unsigned int Offset = 0;
};
