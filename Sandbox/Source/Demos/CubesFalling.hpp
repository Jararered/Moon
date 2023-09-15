#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"
#include "Meshes/Square.hpp"

#include "Utilities/TextureMap.hpp"

extern Coordinator g_Coordinator;

class CubesFalling final : public Engine
{
public:
    void CreatePlatform()
    {
        const auto mesh = std::make_shared<TexturedCubeMesh>();
        const auto shaderID = Shader("Shaders/PositionNormalTexture.vert", "Shaders/PositionNormalTexture.frag");
        const auto textureID = Texture("Textures/terrain.png");
        // const auto texturemap = TextureMap(16, 16, )

        const Entity entity = g_Coordinator.CreateEntity();
        g_Coordinator.AddComponent<Mesh>(entity, Mesh{mesh});
        g_Coordinator.AddComponent<Shader>(entity, Shader{shaderID});
        g_Coordinator.AddComponent<Texture>(entity, Texture{textureID});
        g_Coordinator.AddComponent<Transform>(entity, Transform{.Position = {0, 0, 0}, .Rotation = {0, 0, 0}, .Scale = {500, 1, 500}});
    }

    void CreateCubes()
    {
        const unsigned int count = 9999;

        const auto mesh = std::make_shared<TexturedCubeMesh>();
        const auto shaderID = Shader("Shaders/PositionNormalTexture.vert", "Shaders/PositionNormalTexture.frag");
        for (unsigned int i = 0; i < count; i++)
        {
            const float x = Random::Value<float>(-100, 100);
            const float y = Random::Value<float>(0, 10000);
            const float z = Random::Value<float>(-100, 100);
            const float random = Random::Value<float>(1, 10);

            const Entity entity = g_Coordinator.CreateEntity();
            g_Coordinator.AddComponent<Mesh>(entity, mesh);
            g_Coordinator.AddComponent<Shader>(entity, shaderID);
            g_Coordinator.AddComponent<Texture>(entity);
            g_Coordinator.AddComponent<Index>(entity, Index{0});
            g_Coordinator.AddComponent<Transform>(entity, Transform{.Position = {x, y, z}, .Rotation = {0, 0, 0}, .Scale = {1, random, 1}});
            g_Coordinator.AddComponent<Dynamics>(entity, Dynamics{.Velocity{0, 0, 0}, .Acceleration{0, 0, 0}});
        }
    }
};