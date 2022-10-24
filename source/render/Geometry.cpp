#include "Geometry.hpp"

Vertex::Vertex(glm::vec3 position,
               glm::vec2 textureCoordinate,
               glm::vec3 normal) : Position(position), TextureCoordinate(textureCoordinate), Normal(normal) {}