#pragma once

#include <glm/vec3.hpp>

typedef glm::ivec3 Index;

static Index GetIndex(const glm::vec3& position, unsigned int scale)
{
    assert(scale > 0);

    Index index;
    position.x / scale < 0 ? index.x = position.x / scale - 1 : index.x = position.x / scale;
    position.y / scale < 0 ? index.y = position.y / scale - 1 : index.y = position.y / scale;
    position.z / scale < 0 ? index.z = position.z / scale - 1 : index.z = position.z / scale;
    return index;
}