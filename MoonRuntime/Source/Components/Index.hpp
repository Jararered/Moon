#pragma once

#include <glm/glm.hpp>

typedef glm::ivec3 Index;

static Index GetIndex(const glm::vec3& position, float scale)
{
    assert(scale > 0);

    glm::ivec3 index = glm::floor(position / scale);
    return index;
}
