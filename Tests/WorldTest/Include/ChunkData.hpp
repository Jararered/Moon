#pragma once

#include <array>
#include <glm/vec3.hpp>

#include "Block.hpp"
#include "ChunkConfiguration.hpp"
#include "ChunkGenerator.hpp"

class ChunkData
{
public:
    ChunkData() = default;
    ~ChunkData() = default;

    ChunkData(const glm::vec3& index)
    {
        m_ChunkIndex = index;
        Allocate();

        ChunkGenerator::Initialize();
        GeneratePlanet();
    }

    void Allocate()
    {
        m_BlockData.fill(Block(0));
        m_HeightData.fill(0);
    }

    Block GetBlock(const glm::ivec3& chunkPos)
    {
        if (chunkPos.x < 0 || chunkPos.y < 0 || chunkPos.z < 0)
            return Block(0);

        if (chunkPos.x == CHUNK_SIZE || chunkPos.y == CHUNK_SIZE || chunkPos.z == CHUNK_SIZE)
            return Block(0);

        return m_BlockData.at(chunkPos.x * CHUNK_SIZE * CHUNK_SIZE + chunkPos.y * CHUNK_SIZE + chunkPos.z);
    }

    void SetBlock(const glm::ivec3& chunkPos, const Block& block) { m_BlockData.at(chunkPos.x * CHUNK_SIZE * CHUNK_SIZE + chunkPos.y * CHUNK_SIZE + chunkPos.z) = block; }

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

                    float endCutoffDistance = 50.0f;
                    float startCutoffDistance = 40.0f;
                    float cutoffFactor = 0.0f;

                    if (yGlobal > startCutoffDistance)
                        cutoffFactor = (yGlobal - startCutoffDistance) / (endCutoffDistance - startCutoffDistance);

                    float noise = ChunkGenerator::Get3DNoise(xGlobal, yGlobal, zGlobal);

                    noise += cutoffFactor;

                    if (noise < 0.8f)
                    {
                        SetBlock({x, y, z}, Block(1));
                    }
                }
            }
        }
    }

    glm::ivec3 GetChunkIndex() const { return m_ChunkIndex; }
    void SetChunkIndex(const glm::ivec3& chunkIndex) { m_ChunkIndex = chunkIndex; }

private:
    std::array<Block, CHUNK_VOLUME> m_BlockData;
    std::array<int, CHUNK_SIZE * CHUNK_SIZE> m_HeightData;
    glm::ivec3 m_ChunkIndex = {0, 0, 0};
};