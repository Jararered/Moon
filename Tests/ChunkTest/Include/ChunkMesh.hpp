#pragma once

#include <Mesh.hpp>

#include "ChunkConfiguration.hpp"
#include "ChunkData.hpp"
#include "Block.hpp"

#include <iostream>

class ChunkMesh : public Mesh
{
public:
    ChunkMesh(ChunkData* chunkData)
    {
        Block currentBlock, pxBlock, nxBlock, pyBlock, nyBlock, pzBlock, nzBlock;
        bool px = false, nx = false, py = false, ny = false, pz = false, nz = false;

        for (int x = 0; x < CHUNK_SIZE; x++)
        {
            for (int y = 0; y < CHUNK_SIZE; y++)
            {
                for (int z = 0; z < CHUNK_SIZE; z++)
                {
                    currentBlock = chunkData->GetBlock({ x, y, z });

                    // If the block is air, add no m_Geometry
                    if (currentBlock.GetID() == 0)
                        continue;

                    // Getting block IDs of surrounding blocks
                    pxBlock = chunkData->GetBlock({ x + 1, y, z });
                    nxBlock = chunkData->GetBlock({ x - 1, y, z });

                    pyBlock = chunkData->GetBlock({ x, y + 1, z });
                    nyBlock = chunkData->GetBlock({ x, y - 1, z });

                    pzBlock = chunkData->GetBlock({ x, y, z + 1 });
                    nzBlock = chunkData->GetBlock({ x, y, z - 1 });

                    glm::vec3 color = { 1.0f, 1.0f, 1.0f };

                    float xGlobal = x + chunkData->GetChunkIndex().x * CHUNK_SIZE;
                    float yGlobal = y + chunkData->GetChunkIndex().y * CHUNK_SIZE;
                    float zGlobal = z + chunkData->GetChunkIndex().z * CHUNK_SIZE;

                    // +X Quad
                    if (pxBlock.GetID() == 0)
                    {
                        m_Geometry.Indices.insert(m_Geometry.Indices.end(), { 0 + m_Geometry.Offset, 1 + m_Geometry.Offset, 2 + m_Geometry.Offset, 2 + m_Geometry.Offset, 3 + m_Geometry.Offset, 0 + m_Geometry.Offset });
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal + 0.5f, yGlobal + 0.5f, zGlobal + 0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal + 0.5f, yGlobal - 0.5f, zGlobal + 0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal + 0.5f, yGlobal - 0.5f, zGlobal - 0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal + 0.5f, yGlobal + 0.5f, zGlobal - 0.5f }, color, glm::vec3(1.0f, 0.0f, 0.0f));
                        m_Geometry.Offset = m_Geometry.Offset + 4;
                    }

                    // -X Quad
                    if (nxBlock.GetID() == 0)
                    {
                        m_Geometry.Indices.insert(m_Geometry.Indices.end(), { 0 + m_Geometry.Offset, 1 + m_Geometry.Offset, 2 + m_Geometry.Offset, 2 + m_Geometry.Offset, 3 + m_Geometry.Offset, 0 + m_Geometry.Offset });
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal - 0.5f, yGlobal + 0.5f, zGlobal - 0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal - 0.5f, yGlobal - 0.5f, zGlobal - 0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal - 0.5f, yGlobal - 0.5f, zGlobal + 0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal - 0.5f, yGlobal + 0.5f, zGlobal + 0.5f }, color, glm::vec3(-1.0f, 0.0f, 0.0f));
                        m_Geometry.Offset = m_Geometry.Offset + 4;
                    }

                    // +Y Quad
                    if (pyBlock.GetID() == 0)
                    {
                        m_Geometry.Indices.insert(m_Geometry.Indices.end(), { 0 + m_Geometry.Offset, 1 + m_Geometry.Offset, 2 + m_Geometry.Offset, 2 + m_Geometry.Offset, 3 + m_Geometry.Offset, 0 + m_Geometry.Offset });
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal + 0.5f, yGlobal + 0.5f, zGlobal - 0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal - 0.5f, yGlobal + 0.5f, zGlobal - 0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal - 0.5f, yGlobal + 0.5f, zGlobal + 0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal + 0.5f, yGlobal + 0.5f, zGlobal + 0.5f }, color, glm::vec3(0.0f, 1.0f, 0.0f));
                        m_Geometry.Offset = m_Geometry.Offset + 4;
                    }

                    // -Y Quad
                    if (nyBlock.GetID() == 0)
                    {
                        m_Geometry.Indices.insert(m_Geometry.Indices.end(), { 0 + m_Geometry.Offset, 1 + m_Geometry.Offset, 2 + m_Geometry.Offset, 2 + m_Geometry.Offset, 3 + m_Geometry.Offset, 0 + m_Geometry.Offset });
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal + 0.5f, yGlobal - 0.5f, zGlobal - 0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal + 0.5f, yGlobal - 0.5f, zGlobal + 0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal - 0.5f, yGlobal - 0.5f, zGlobal + 0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal - 0.5f, yGlobal - 0.5f, zGlobal - 0.5f }, color, glm::vec3(0.0f, -1.0f, 0.0f));
                        m_Geometry.Offset = m_Geometry.Offset + 4;
                    }

                    // +Z Quad
                    if (pzBlock.GetID() == 0)
                    {
                        m_Geometry.Indices.insert(m_Geometry.Indices.end(), { 0 + m_Geometry.Offset, 1 + m_Geometry.Offset, 2 + m_Geometry.Offset, 2 + m_Geometry.Offset, 3 + m_Geometry.Offset, 0 + m_Geometry.Offset });
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal - 0.5f, yGlobal - 0.5f, zGlobal + 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal + 0.5f, yGlobal - 0.5f, zGlobal + 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal + 0.5f, yGlobal + 0.5f, zGlobal + 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal - 0.5f, yGlobal + 0.5f, zGlobal + 0.5f }, color, glm::vec3(0.0f, 0.0f, 1.0f));
                        m_Geometry.Offset = m_Geometry.Offset + 4;
                    }

                    // -Z Quad
                    if (nzBlock.GetID() == 0)
                    {
                        m_Geometry.Indices.insert(m_Geometry.Indices.end(), { 0 + m_Geometry.Offset, 1 + m_Geometry.Offset, 2 + m_Geometry.Offset, 2 + m_Geometry.Offset, 3 + m_Geometry.Offset, 0 + m_Geometry.Offset });
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal + 0.5f, yGlobal - 0.5f, zGlobal - 0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal - 0.5f, yGlobal - 0.5f, zGlobal - 0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal - 0.5f, yGlobal + 0.5f, zGlobal - 0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f));
                        m_Geometry.Vertices.emplace_back(glm::vec3{ xGlobal + 0.5f, yGlobal + 0.5f, zGlobal - 0.5f }, color, glm::vec3(0.0f, 0.0f, -1.0f));
                        m_Geometry.Offset = m_Geometry.Offset + 4;
                    }
                }
            }
        }
        Generate();
    }
};