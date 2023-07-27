#pragma once

#include <Entity.hpp>

#include "ChunkMesh.hpp"
#include "ChunkData.hpp"

#include <array>

class ChunkEntity : public Entity
{
private:
    ChunkData m_ChunkData;

public:
    ChunkEntity(glm::ivec3 index)
    {
        m_ChunkData.SetChunkIndex(index);
        m_ChunkData.Allocate();

        // m_ChunkData.GenerateStone();
        m_ChunkData.GeneratePlanet();

        p_Mesh = new ChunkMesh(&m_ChunkData);
    }

    ~ChunkEntity()
    {
        delete p_Mesh;
        delete p_Collision;
    }

};