#pragma once

#include <Entity.hpp>

#include "ChunkData.hpp"
#include "ChunkMesh.hpp"

#include <array>

class ChunkEntity : public Entity
{
public:
    ChunkEntity() = default;
    ~ChunkEntity() = default;

    void Update(float dt) override {}

private:
    ChunkData m_ChunkData;
};