#include "Geometry.hpp"

Vertex::Vertex(glm::vec3 position) :
    Position(position)
{
}

Vertex::Vertex(glm::vec3 position, glm::vec3 color) :
    Position(position),
    Color(color)
{
}

Vertex::Vertex(glm::vec3 position, glm::vec3 color, glm::vec3 normal) :
    Position(position),
    Color(color),
    Normal(normal)
{
}