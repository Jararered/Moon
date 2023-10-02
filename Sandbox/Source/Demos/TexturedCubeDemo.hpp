#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"
#include "Meshes/Square.hpp"

#include "Utilities/TextureMap.hpp"

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
                    const Entity entity = m_Scenario->CreateEntity();
                    m_Scenario->AddComponent<Mesh>(entity, mesh);
                    m_Scenario->AddComponent<Shader>(entity, shader);
                    m_Scenario->AddComponent<Texture>(entity, texture);
                    m_Scenario->AddComponent<Transform>(entity, Transform{.Position{x, y, z}});
                }
            }
        }
    }
};