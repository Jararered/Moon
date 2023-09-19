#pragma once

#include <Moon.hpp>

#include "Meshes/ChunkMesh.hpp"

extern Coordinator e_Coordinator;

class ChunkDemo final : public Engine
{
public:
    void CreateScene()
    {
        const auto shader = Shader("Shaders/PositionNormalTexture.vert", "Shaders/NormalLighting.frag");
        const auto texture = Texture("Textures/terrain.png");

        ChunkMesh::s_TextureMap.Configure(texture.Width, texture.Height, 16);
        ChunkData::s_ChunkGenerator.SetSeed(34587);
        ChunkData::s_ChunkGenerator.SetFrequency(0.03f);

        const int xSpan = 0;
        const int ySpan = 1;
        const int zSpan = 0;

        for (int x = -xSpan; x <= xSpan; x++)
        {
            for (int y = 0; y <= ySpan; y++)
            {
                for (int z = -zSpan; z <= zSpan; z++)
                {
                    const auto chunkData = std::make_shared<ChunkData>(glm::ivec3(x, y, z));
                    const auto mesh = std::make_shared<ChunkMesh>(chunkData);

                    Entity entity = e_Coordinator.CreateEntity();
                    e_Coordinator.AddComponent<Mesh>(entity, mesh);
                    e_Coordinator.AddComponent<Transform>(entity, Transform{.Position = {x * c_ChunkSize, y * c_ChunkSize, z * c_ChunkSize}});
                    e_Coordinator.AddComponent<Shader>(entity, shader);
                    e_Coordinator.AddComponent<Texture>(entity, texture);
                }
            }
        }
    }
};

DepricatedTextureMap ChunkMesh::s_TextureMap = DepricatedTextureMap();
NoiseGenerator ChunkData::s_ChunkGenerator = NoiseGenerator();