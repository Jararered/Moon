#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

struct Vertex
{
    Vertex(glm::vec3 position);

    glm::vec3 Position;
};

struct Geometry
{
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    unsigned int Offset = 0;
};
