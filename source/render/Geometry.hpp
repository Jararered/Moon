#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

struct Vertex
{
    Vertex(glm::vec3 position,
           glm::vec2 textureCoordinate,
           glm::vec3 normal);

    glm::vec3 Position;
    glm::vec2 TextureCoordinate;
    glm::vec3 Normal;
};

struct Geometry
{
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    unsigned int Offset;
};
