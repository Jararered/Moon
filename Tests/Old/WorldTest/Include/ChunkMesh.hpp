#pragma once

#include <Mesh.hpp>

#include "Block.hpp"
#include "ChunkConfiguration.hpp"
#include "ChunkData.hpp"

#include <iostream>

class ChunkMesh : public Mesh<Vertex3D<glm::vec3, glm::vec3, glm::vec3>>
{
public:
    ChunkMesh() = delete;
    virtual ~ChunkMesh() override = default;

    ChunkMesh(ChunkData* chunkData)
    {
        auto& vertices = m_VertexBuffer.GetVertices();
        auto& indices = m_VertexBuffer.GetIndices();
        unsigned int offset = 0;

        Block currentBlock, pxBlock, nxBlock, pyBlock, nyBlock, pzBlock, nzBlock;
        bool px = false, nx = false, py = false, ny = false, pz = false, nz = false;

        for (int x = 0; x < CHUNK_SIZE; x++)
        {
            for (int y = 0; y < CHUNK_SIZE; y++)
            {
                for (int z = 0; z < CHUNK_SIZE; z++)
                {
                    currentBlock = chunkData->GetBlock({x, y, z});

                    // If the block is air, add no
                    if (currentBlock.GetID() == 0)
                        continue;

                    // Getting block IDs of surrounding blocks
                    pxBlock = chunkData->GetBlock({x + 1, y, z});
                    nxBlock = chunkData->GetBlock({x - 1, y, z});
                    pyBlock = chunkData->GetBlock({x, y + 1, z});
                    nyBlock = chunkData->GetBlock({x, y - 1, z});
                    pzBlock = chunkData->GetBlock({x, y, z + 1});
                    nzBlock = chunkData->GetBlock({x, y, z - 1});

                    glm::vec3 color = {1.0f, 1.0f, 1.0f};

                    float xGlobal = x + chunkData->GetChunkIndex().x * CHUNK_SIZE;
                    float yGlobal = y + chunkData->GetChunkIndex().y * CHUNK_SIZE;
                    float zGlobal = z + chunkData->GetChunkIndex().z * CHUNK_SIZE;

                    // +X Quad
                    if (pxBlock.GetID() == 0)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal + 0.5f, yGlobal + 0.5f, zGlobal + 0.5f}, color, glm::vec3(1.0f, 0.0f, 0.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal + 0.5f, yGlobal - 0.5f, zGlobal + 0.5f}, color, glm::vec3(1.0f, 0.0f, 0.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal + 0.5f, yGlobal - 0.5f, zGlobal - 0.5f}, color, glm::vec3(1.0f, 0.0f, 0.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal + 0.5f, yGlobal + 0.5f, zGlobal - 0.5f}, color, glm::vec3(1.0f, 0.0f, 0.0f)));
                        offset = offset + 4;
                    }

                    // -X Quad
                    if (nxBlock.GetID() == 0)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal - 0.5f, yGlobal + 0.5f, zGlobal - 0.5f}, color, glm::vec3(-1.0f, 0.0f, 0.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal - 0.5f, yGlobal - 0.5f, zGlobal - 0.5f}, color, glm::vec3(-1.0f, 0.0f, 0.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal - 0.5f, yGlobal - 0.5f, zGlobal + 0.5f}, color, glm::vec3(-1.0f, 0.0f, 0.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal - 0.5f, yGlobal + 0.5f, zGlobal + 0.5f}, color, glm::vec3(-1.0f, 0.0f, 0.0f)));
                        offset = offset + 4;
                    }

                    // +Y Quad
                    if (pyBlock.GetID() == 0)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal + 0.5f, yGlobal + 0.5f, zGlobal - 0.5f}, color, glm::vec3(0.0f, 1.0f, 0.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal - 0.5f, yGlobal + 0.5f, zGlobal - 0.5f}, color, glm::vec3(0.0f, 1.0f, 0.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal - 0.5f, yGlobal + 0.5f, zGlobal + 0.5f}, color, glm::vec3(0.0f, 1.0f, 0.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal + 0.5f, yGlobal + 0.5f, zGlobal + 0.5f}, color, glm::vec3(0.0f, 1.0f, 0.0f)));
                        offset = offset + 4;
                    }

                    // -Y Quad
                    if (nyBlock.GetID() == 0)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal + 0.5f, yGlobal - 0.5f, zGlobal - 0.5f}, color, glm::vec3(0.0f, -1.0f, 0.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal + 0.5f, yGlobal - 0.5f, zGlobal + 0.5f}, color, glm::vec3(0.0f, -1.0f, 0.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal - 0.5f, yGlobal - 0.5f, zGlobal + 0.5f}, color, glm::vec3(0.0f, -1.0f, 0.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal - 0.5f, yGlobal - 0.5f, zGlobal - 0.5f}, color, glm::vec3(0.0f, -1.0f, 0.0f)));
                        offset = offset + 4;
                    }

                    // +Z Quad
                    if (pzBlock.GetID() == 0)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal - 0.5f, yGlobal - 0.5f, zGlobal + 0.5f}, color, glm::vec3(0.0f, 0.0f, 1.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal + 0.5f, yGlobal - 0.5f, zGlobal + 0.5f}, color, glm::vec3(0.0f, 0.0f, 1.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal + 0.5f, yGlobal + 0.5f, zGlobal + 0.5f}, color, glm::vec3(0.0f, 0.0f, 1.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal - 0.5f, yGlobal + 0.5f, zGlobal + 0.5f}, color, glm::vec3(0.0f, 0.0f, 1.0f)));
                        offset = offset + 4;
                    }

                    // -Z Quad
                    if (nzBlock.GetID() == 0)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal + 0.5f, yGlobal - 0.5f, zGlobal - 0.5f}, color, glm::vec3(0.0f, 0.0f, -1.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal - 0.5f, yGlobal - 0.5f, zGlobal - 0.5f}, color, glm::vec3(0.0f, 0.0f, -1.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal - 0.5f, yGlobal + 0.5f, zGlobal - 0.5f}, color, glm::vec3(0.0f, 0.0f, -1.0f)));
                        AddToVertexBuffer(Vertex3D<glm::vec3, glm::vec3, glm::vec3>(glm::vec3{xGlobal + 0.5f, yGlobal + 0.5f, zGlobal - 0.5f}, color, glm::vec3(0.0f, 0.0f, -1.0f)));
                        offset = offset + 4;
                    }
                }
            }
        }
        m_VertexBuffer.Generate();
    }
};