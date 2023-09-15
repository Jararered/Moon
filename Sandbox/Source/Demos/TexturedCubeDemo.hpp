#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"
#include "Meshes/Square.hpp"

#include "Utilities/TextureMap.hpp"

extern Coordinator g_Coordinator;

class TexturedCubeDemo final : public Engine
{
public:
    void CreateScene()
    {
        const auto mesh = std::make_shared<TexturedCubeMesh>();
        const auto shaderID = Shader("Shaders/PositionNormalTexture.vert", "Shaders/PositionNormalTexture.frag");
        const auto textureID = Texture("Textures/terrain.png");

        for (int x = -10; x < 10; x += 2)
        {
            for (int y = -10; y < 10; y += 2)
            {
                for (int z = -10; z < 10; z += 2)
                {
                    const Entity entity = g_Coordinator.CreateEntity();
                    g_Coordinator.AddComponent<Mesh>(entity, mesh);
                    g_Coordinator.AddComponent<Shader>(entity, shaderID);
                    g_Coordinator.AddComponent<Texture>(entity, textureID);
                    g_Coordinator.AddComponent<Transform>(entity, Transform{.Position{x, y, z}});
                }
            }
        }
    }
};