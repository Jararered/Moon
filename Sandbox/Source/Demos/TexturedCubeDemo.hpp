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
        const auto shaderID = Shader::CreateShader("Shaders/PositionNormalTexture.vert", "Shaders/PositionNormalTexture.frag");
        const auto textureID = Texture::CreateTexture("Textures/terrain.png");

        const Entity entity = g_Coordinator.CreateEntity();
        g_Coordinator.AddComponent<Mesh>(entity, Mesh{mesh});
        g_Coordinator.AddComponent<Shader>(entity, Shader{shaderID});
        g_Coordinator.AddComponent<Texture>(entity, Texture{textureID});
        g_Coordinator.AddComponent<Transform>(entity, Transform{});
    }
};