#pragma once

#include <Mesh.hpp>

#include "Block.hpp"
#include "ChunkConfiguration.hpp"
#include "ChunkData.hpp"

#include <iostream>

class ChunkMesh : public TMeshComponent<Vertex2D<glm::vec3, glm::vec3>> // Position, Normal
{
public:
    virtual ~ChunkMesh() override = default;

    ChunkMesh(ChunkData* chunkData)
    {
        auto& vertices = VertexBuffer.GetVertices();
        auto& indices = VertexBuffer.GetIndices();
        unsigned int offset = 0;

        for (int z = 0; z < CHUNK_SIZE; z++)
        {
            for (int y = 0; y < CHUNK_SIZE; y++)
            {
                for (int x = 0; x < CHUNK_SIZE; x++)
                {
                    const int currentBlockID = chunkData->GetBlock(x, y, z).GetID();
                    bool px = true, nx = true, py = true, ny = true, pz = true, nz = true;

                    if (currentBlockID == 0)
                        continue;

                    if (x > 0)
                        nx = chunkData->GetBlock(x - 1, y, z).GetID() == 0;
                    if (x < CHUNK_SIZE - 1)
                        px = chunkData->GetBlock(x + 1, y, z).GetID() == 0;
                    if (y > 0)
                        ny = chunkData->GetBlock(x, y - 1, z).GetID() == 0;
                    if (y < CHUNK_SIZE - 1)
                        py = chunkData->GetBlock(x, y + 1, z).GetID() == 0;
                    if (z > 0)
                        nz = chunkData->GetBlock(x, y, z - 1).GetID() == 0;
                    if (z < CHUNK_SIZE - 1)
                        pz = chunkData->GetBlock(x, y, z + 1).GetID() == 0;

                    if (px)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x + 0.5f, y + 0.5f, z + 0.5f}, {1.0f, 0.0f, 0.0f}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x + 0.5f, y - 0.5f, z + 0.5f}, {1.0f, 0.0f, 0.0f}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x + 0.5f, y - 0.5f, z - 0.5f}, {1.0f, 0.0f, 0.0f}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x + 0.5f, y + 0.5f, z - 0.5f}, {1.0f, 0.0f, 0.0f}));
                        offset += 4;
                    }

                    if (nx)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x - 0.5f, y + 0.5f, z - 0.5f}, {-1.0f, 0.0f, 0.0}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x - 0.5f, y - 0.5f, z - 0.5f}, {-1.0f, 0.0f, 0.0}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x - 0.5f, y - 0.5f, z + 0.5f}, {-1.0f, 0.0f, 0.0}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x - 0.5f, y + 0.5f, z + 0.5f}, {-1.0f, 0.0f, 0.0}));
                        offset += 4;
                    }

                    if (py)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x + 0.5f, y + 0.5f, z - 0.5f}, {0.0f, 1.0f, 0.0f}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x - 0.5f, y + 0.5f, z - 0.5f}, {0.0f, 1.0f, 0.0f}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x - 0.5f, y + 0.5f, z + 0.5f}, {0.0f, 1.0f, 0.0f}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x + 0.5f, y + 0.5f, z + 0.5f}, {0.0f, 1.0f, 0.0f}));
                        offset += 4;
                    }

                    if (ny)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x + 0.5f, y - 0.5f, z - 0.5f}, {0.0f, -1.0f, 0.0}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x + 0.5f, y - 0.5f, z + 0.5f}, {0.0f, -1.0f, 0.0}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x - 0.5f, y - 0.5f, z + 0.5f}, {0.0f, -1.0f, 0.0}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x - 0.5f, y - 0.5f, z - 0.5f}, {0.0f, -1.0f, 0.0}));
                        offset += 4;
                    }

                    if (pz)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x - 0.5f, y - 0.5f, z + 0.5f}, {0.0f, 0.0f, 1.0f}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x + 0.5f, y - 0.5f, z + 0.5f}, {0.0f, 0.0f, 1.0f}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x + 0.5f, y + 0.5f, z + 0.5f}, {0.0f, 0.0f, 1.0f}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x - 0.5f, y + 0.5f, z + 0.5f}, {0.0f, 0.0f, 1.0f}));
                        offset += 4;
                    }

                    if (nz)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x + 0.5f, y - 0.5f, z - 0.5f}, {0.0f, 0.0f, -1.0}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x - 0.5f, y - 0.5f, z - 0.5f}, {0.0f, 0.0f, -1.0}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x - 0.5f, y + 0.5f, z - 0.5f}, {0.0f, 0.0f, -1.0}));
                        vertices.emplace_back(Vertex2D<glm::vec3, glm::vec3>({x + 0.5f, y + 0.5f, z - 0.5f}, {0.0f, 0.0f, -1.0}));
                        offset += 4;
                    }
                }
            }
        }
        VertexBuffer.Generate();
    }
};