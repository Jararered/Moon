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

        const int xSpan = 2;
        const int ySpan = 0;
        const int zSpan = 2;

        for (int x = -xSpan; x <= xSpan; x++)
        {
            for (int y = 0; y <= ySpan; y++)
            {
                for (int z = -zSpan; z <= zSpan; z++)
                {
                    // ChunkData::s_ChunkGenerator = ChunkGenerator(34587, 0.03f);
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
