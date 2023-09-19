#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"
#include "Meshes/Square.hpp"

#include "Utilities/TextureMap.hpp"

extern Coordinator e_Coordinator;

class TexturedCubeDemo final : public Engine
{
public:
    void CreateScene()
    {
        const auto mesh = std::make_shared<TexturedCubeMesh>();
        const auto shader = Shader("Shaders/PositionNormalTexture.vert", "Shaders/PositionNormalTexture.frag");
        const auto texture = Texture("Textures/terrain.png");

        for (int x = -10; x < 10; x += 2)
        {
            for (int y = -10; y < 10; y += 2)
            {
                for (int z = -10; z < 10; z += 2)
                {
                    const Entity entity = e_Coordinator.CreateEntity();
                    e_Coordinator.AddComponent<Mesh>(entity, mesh);
                    e_Coordinator.AddComponent<Shader>(entity, shader);
                    e_Coordinator.AddComponent<Texture>(entity, texture);
                    e_Coordinator.AddComponent<Transform>(entity, Transform{.Position{x, y, z}});
                }
            }
        }
    }
};