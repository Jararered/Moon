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

        const Entity entity = g_Coordinator.CreateEntity();
        g_Coordinator.AddComponent<Mesh>(entity, mesh);
        g_Coordinator.AddComponent<Shader>(entity, shaderID);
        g_Coordinator.AddComponent<Texture>(entity, textureID);
        g_Coordinator.AddComponent<Transform>(entity);
        g_Coordinator.AddComponent<Dynamics>(entity);
    }
};