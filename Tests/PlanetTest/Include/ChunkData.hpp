#pragma once

#include <array>
#include <glm/vec3.hpp>

#include "ChunkGenerator.hpp"
#include "ChunkConfiguration.hpp"
#include "Block.hpp"

class ChunkData
{
public:
    ChunkData() {}
    ~ChunkData() {}

    void Allocate()
    {
        m_BlockData.fill(Block(0));
        m_HeightData.fill(0);

        ChunkGenerator::Initialize();
    }

    Block GetBlock(glm::ivec3 chunkPos)
    {
        if (chunkPos.x < 0 || chunkPos.y < 0 || chunkPos.z < 0)
            return Block();

        if (chunkPos.x == CHUNK_SIZE || chunkPos.y == CHUNK_SIZE || chunkPos.z == CHUNK_SIZE)
            return Block();

        return m_BlockData.at(chunkPos.x * CHUNK_SIZE * CHUNK_SIZE + chunkPos.y * CHUNK_SIZE + chunkPos.z);
    }

    void SetBlock(glm::ivec3 chunkPos, Block block)
    {
        m_BlockData.at(chunkPos.x * CHUNK_SIZE * CHUNK_SIZE + chunkPos.y * CHUNK_SIZE + chunkPos.z) = block;
    }

    void GeneratePlanet()
    {
        for (int x = 0; x < CHUNK_SIZE; x++)
        {
            for (int y = 0; y < CHUNK_SIZE; y++)
            {
                for (int z = 0; z < CHUNK_SIZE; z++)
                {
                    float xGlobal = x + m_ChunkIndex.x * CHUNK_SIZE;
                    float yGlobal = y + m_ChunkIndex.y * CHUNK_SIZE;
                    float zGlobal = z + m_ChunkIndex.z * CHUNK_SIZE;
                    float distanceFromOrigin = glm::sqrt(xGlobal * xGlobal + yGlobal * yGlobal + zGlobal * zGlobal);

                    float endCutoffDistance = 50.0f;
                    float startCutoffDistance = 45.0f;
                    float cutoffFactor = 0.0f;

                    if (distanceFromOrigin > startCutoffDistance)
                        cutoffFactor = (distanceFromOrigin - startCutoffDistance) / (endCutoffDistance - startCutoffDistance);
                    
                    float noise = ChunkGenerator::Get3DNoise(xGlobal, yGlobal, zGlobal);

                    noise += cutoffFactor;

                    if (noise < 0.95f)
                    {
                        SetBlock({ x, y, z }, Block(1));
                    }
                }
            }
        }
    }

    glm::ivec3 GetChunkIndex() const { return m_ChunkIndex; }
    void SetChunkIndex(const glm::ivec3& chunkIndex) { m_ChunkIndex = chunkIndex; }

private:
    std::array<Block, CHUNK_VOLUME> m_BlockData;
    std::array<int, CHUNK_SIZE* CHUNK_SIZE> m_HeightData;
    glm::ivec3 m_ChunkIndex = { 0, 0, 0 };
};