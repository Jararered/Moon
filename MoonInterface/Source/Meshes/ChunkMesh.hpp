#pragma once

#include <Components/Mesh.hpp>

#include <FastNoiseLite.h>
#include <octree/octree.h>

constexpr int c_ChunkSize = 32;
constexpr int CHUNK_VOLUME = c_ChunkSize * c_ChunkSize * c_ChunkSize;

class DepricatedTextureMap
{
public:
    void Configure(int width, int height, int resolution)
    {
        if (!(width > 0) or !(width < 10000) or !(height > 0) or !(height < 10000))
            return;

        for (int j = 0; j < height; j += resolution)
        {
            for (int i = 0; i < width; i += resolution)
            {
                const float left = static_cast<float>(i) / static_cast<float>(width);
                const float bottom = static_cast<float>(j) / static_cast<float>(height);
                const float right = (static_cast<float>(i) + static_cast<float>(resolution)) / static_cast<float>(width);
                const float top = (static_cast<float>(j) + static_cast<float>(resolution)) / static_cast<float>(height);

                m_Coordinates.push_back({left, right, bottom, top});
            }
        }
    }

    [[nodiscard]] std::vector<std::vector<float>> TextureCoordinates() { return m_Coordinates; }
    [[nodiscard]] glm::vec2 TopLeft(int index) { return {m_Coordinates[index][0], m_Coordinates[index][2]}; }
    [[nodiscard]] glm::vec2 TopRight(int index) { return {m_Coordinates[index][1], m_Coordinates[index][2]}; }
    [[nodiscard]] glm::vec2 BottomLeft(int index) { return {m_Coordinates[index][0], m_Coordinates[index][3]}; }
    [[nodiscard]] glm::vec2 BottomRight(int index) { return {m_Coordinates[index][1], m_Coordinates[index][3]}; }

private:
    // vector of 4x1 vectors (left, right, bottom, top coordinates)
    std::vector<std::vector<float>> m_Coordinates;
};

class NoiseGenerator final
{
public:
    void SetSeed(int seed = 0) { m_Noise.SetSeed(seed); }
    void SetFrequency(float frequency = 0.03f) { m_Noise.SetFrequency(frequency); }

    template <class T> [[nodiscard]] T Get3DNoise(int x, int y, int z) { return m_Noise.GetNoise(static_cast<T>(x), static_cast<T>(y), static_cast<T>(z)); }

private:
    FastNoiseLite m_Noise;
};

class ChunkData final
{
public:
    struct Block final
    {
        Block(int id) : ID(id){};
        unsigned int ID = 0;
    };

public:
    ChunkData(const glm::vec3& index) : m_ChunkIndex(index) { GenerateChunkData(); }

    static NoiseGenerator s_ChunkGenerator;

    [[nodiscard]] const Block& GetBlock(int x, int y, int z) { return m_OctreeData.at(x, y, z); }
    [[nodiscard]] const glm::ivec3& GetChunkIndex() const { return m_ChunkIndex; }
    void SetBlock(int x, int y, int z, const Block& block) { m_OctreeData(x, y, z) = block; }

    void GenerateChunkData()
    {
        m_OctreeData.setEmptyValue(Block{.ID = 0});
        for (int z = 0; z < c_ChunkSize; z++)
        {
            const float zGlobal = z + m_ChunkIndex.z * c_ChunkSize;
            for (int y = 0; y < c_ChunkSize; y++)
            {
                const float yGlobal = y + m_ChunkIndex.y * c_ChunkSize;
                for (int x = 0; x < c_ChunkSize; x++)
                {
                    const float xGlobal = x + m_ChunkIndex.x * c_ChunkSize;

                    const float endCutoffDistance = 20.0f;
                    const float startCutoffDistance = 10.0f;
                    float cutoffFactor = 0.0f;
                    if (yGlobal > startCutoffDistance)
                    {
                        cutoffFactor = (yGlobal - startCutoffDistance) / (endCutoffDistance - startCutoffDistance);
                    }

                    auto noise = s_ChunkGenerator.Get3DNoise<float>(xGlobal, yGlobal, zGlobal);
                    noise += cutoffFactor;

                    if (noise < 0.8f)
                    {
                        SetBlock(x, y, z, Block{.ID = 1});
                    }
                }
            }
        }
    }

private:
    Octree<Block> m_OctreeData = Octree<Block>(c_ChunkSize);
    glm::ivec3 m_ChunkIndex = {0, 0, 0};
};

class ChunkMesh final : public MeshTemplate<Vertex3D<glm::vec3, glm::vec3, glm::vec2>> // Position, Normal, Texture
{
public:
    static DepricatedTextureMap s_TextureMap;

    ChunkMesh(std::shared_ptr<ChunkData> chunkData)
    {
        using Vertex = Vertex3D<glm::vec3, glm::vec3, glm::vec2>;

        auto& vertices = VertexBuffer.GetVertices();
        auto& indices = VertexBuffer.GetIndices();
        unsigned int offset = 0;

        for (int z = 0; z < c_ChunkSize; z++)
        {
            for (int y = 0; y < c_ChunkSize; y++)
            {
                for (int x = 0; x < c_ChunkSize; x++)
                {
                    const int currentBlockID = chunkData->GetBlock(x, y, z).ID;

                    if (currentBlockID == 0)
                        continue;

                    bool px = true, nx = true, py = true, ny = true, pz = true, nz = true;
                    if (x > 0)
                        nx = chunkData->GetBlock(x - 1, y, z).ID == 0;
                    if (x < c_ChunkSize - 1)
                        px = chunkData->GetBlock(x + 1, y, z).ID == 0;
                    if (y > 0)
                        ny = chunkData->GetBlock(x, y - 1, z).ID == 0;
                    if (y < c_ChunkSize - 1)
                        py = chunkData->GetBlock(x, y + 1, z).ID == 0;
                    if (z > 0)
                        nz = chunkData->GetBlock(x, y, z - 1).ID == 0;
                    if (z < c_ChunkSize - 1)
                        pz = chunkData->GetBlock(x, y, z + 1).ID == 0;

                    if (px)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        vertices.emplace_back(Vertex({x + 0.5f, y + 0.5f, z + 0.5f}, {1.0f, 0.0f, 0.0f}, s_TextureMap.TopLeft(1)));
                        vertices.emplace_back(Vertex({x + 0.5f, y - 0.5f, z + 0.5f}, {1.0f, 0.0f, 0.0f}, s_TextureMap.BottomLeft(1)));
                        vertices.emplace_back(Vertex({x + 0.5f, y - 0.5f, z - 0.5f}, {1.0f, 0.0f, 0.0f}, s_TextureMap.BottomRight(1)));
                        vertices.emplace_back(Vertex({x + 0.5f, y + 0.5f, z - 0.5f}, {1.0f, 0.0f, 0.0f}, s_TextureMap.TopRight(1)));
                        offset += 4;
                    }

                    if (nx)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        vertices.emplace_back(Vertex({x - 0.5f, y + 0.5f, z - 0.5f}, {-1.0f, 0.0f, 0.0}, s_TextureMap.TopLeft(1)));
                        vertices.emplace_back(Vertex({x - 0.5f, y - 0.5f, z - 0.5f}, {-1.0f, 0.0f, 0.0}, s_TextureMap.BottomLeft(1)));
                        vertices.emplace_back(Vertex({x - 0.5f, y - 0.5f, z + 0.5f}, {-1.0f, 0.0f, 0.0}, s_TextureMap.BottomRight(1)));
                        vertices.emplace_back(Vertex({x - 0.5f, y + 0.5f, z + 0.5f}, {-1.0f, 0.0f, 0.0}, s_TextureMap.TopRight(1)));
                        offset += 4;
                    }

                    if (py)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        vertices.emplace_back(Vertex({x + 0.5f, y + 0.5f, z - 0.5f}, {0.0f, 1.0f, 0.0f}, s_TextureMap.TopRight(1)));
                        vertices.emplace_back(Vertex({x - 0.5f, y + 0.5f, z - 0.5f}, {0.0f, 1.0f, 0.0f}, s_TextureMap.TopLeft(1)));
                        vertices.emplace_back(Vertex({x - 0.5f, y + 0.5f, z + 0.5f}, {0.0f, 1.0f, 0.0f}, s_TextureMap.BottomLeft(1)));
                        vertices.emplace_back(Vertex({x + 0.5f, y + 0.5f, z + 0.5f}, {0.0f, 1.0f, 0.0f}, s_TextureMap.BottomRight(1)));
                        offset += 4;
                    }

                    if (ny)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        vertices.emplace_back(Vertex({x + 0.5f, y - 0.5f, z - 0.5f}, {0.0f, -1.0f, 0.0}, s_TextureMap.BottomRight(1)));
                        vertices.emplace_back(Vertex({x + 0.5f, y - 0.5f, z + 0.5f}, {0.0f, -1.0f, 0.0}, s_TextureMap.TopRight(1)));
                        vertices.emplace_back(Vertex({x - 0.5f, y - 0.5f, z + 0.5f}, {0.0f, -1.0f, 0.0}, s_TextureMap.TopLeft(1)));
                        vertices.emplace_back(Vertex({x - 0.5f, y - 0.5f, z - 0.5f}, {0.0f, -1.0f, 0.0}, s_TextureMap.BottomLeft(1)));
                        offset += 4;
                    }

                    if (pz)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        vertices.emplace_back(Vertex({x - 0.5f, y - 0.5f, z + 0.5f}, {0.0f, 0.0f, 1.0f}, s_TextureMap.BottomLeft(1)));
                        vertices.emplace_back(Vertex({x + 0.5f, y - 0.5f, z + 0.5f}, {0.0f, 0.0f, 1.0f}, s_TextureMap.BottomRight(1)));
                        vertices.emplace_back(Vertex({x + 0.5f, y + 0.5f, z + 0.5f}, {0.0f, 0.0f, 1.0f}, s_TextureMap.TopRight(1)));
                        vertices.emplace_back(Vertex({x - 0.5f, y + 0.5f, z + 0.5f}, {0.0f, 0.0f, 1.0f}, s_TextureMap.TopLeft(1)));
                        offset += 4;
                    }

                    if (nz)
                    {
                        indices.insert(indices.end(), {0 + offset, 1 + offset, 2 + offset, 2 + offset, 3 + offset, 0 + offset});
                        vertices.emplace_back(Vertex({x + 0.5f, y - 0.5f, z - 0.5f}, {0.0f, 0.0f, -1.0}, s_TextureMap.BottomLeft(1)));
                        vertices.emplace_back(Vertex({x - 0.5f, y - 0.5f, z - 0.5f}, {0.0f, 0.0f, -1.0}, s_TextureMap.BottomRight(1)));
                        vertices.emplace_back(Vertex({x - 0.5f, y + 0.5f, z - 0.5f}, {0.0f, 0.0f, -1.0}, s_TextureMap.TopRight(1)));
                        vertices.emplace_back(Vertex({x + 0.5f, y + 0.5f, z - 0.5f}, {0.0f, 0.0f, -1.0}, s_TextureMap.TopLeft(1)));
                        offset += 4;
                    }
                }
            }
        }
        VertexBuffer.BufferData();
    }
};
