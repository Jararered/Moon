#pragma once

#include <array>
#include <glm/vec3.hpp>
#include <octree/octree.h>
#include <print>

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
        m_OctreeData.setEmptyValue(Block(0));

        ChunkGenerator::Initialize();
        GenerateChunkData();
    }

    const Block& GetBlock(int x, int y, int z) { return m_OctreeData.at(x, y, z); }
    void SetBlock(int x, int y, int z, const Block& block) { m_OctreeData(x, y, z) = block; }

    void GenerateChunkData()
    {
        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            float zGlobal = z + m_ChunkIndex.z * CHUNK_SIZE;
            for (int y = 0; y < CHUNK_SIZE; y++)
            {
                float yGlobal = y + m_ChunkIndex.y * CHUNK_SIZE;
                for (int x = 0; x < CHUNK_SIZE; x++)
                {
                    float xGlobal = x + m_ChunkIndex.x * CHUNK_SIZE;

                    float endCutoffDistance = 50.0f;
                    float startCutoffDistance = 40.0f;
                    float cutoffFactor = 0.0f;
                    if (yGlobal > startCutoffDistance)
                        cutoffFactor = (yGlobal - startCutoffDistance) / (endCutoffDistance - startCutoffDistance);

                    float noise = ChunkGenerator::Get3DNoise(xGlobal, yGlobal, zGlobal);
                    noise += cutoffFactor;

                    if (noise < 0.8f)
                        SetBlock(x, y, z, Block(1));
                }
            }
        }
        std::println("Chunk generated, using {} bytes.", m_OctreeData.bytes());
    }

    glm::ivec3 GetChunkIndex() const { return m_ChunkIndex; }

private:
    Octree<Block> m_OctreeData = Octree<Block>(CHUNK_SIZE);
    glm::ivec3 m_ChunkIndex = {0, 0, 0};
};