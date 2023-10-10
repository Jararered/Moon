#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"

class SceneDemo final : public Engine
{
public:
    void CreateScene()
    {
        const unsigned int count = 9999;

        const auto mesh = std::make_shared<TexturedCubeMesh>();
        const auto shaderID = Shader("Shaders/PositionNormalTexture.vert", "Shaders/White.frag");

        const Entity entity = m_Scenario->CreateEntity();
        m_Scenario->AddComponent<Mesh>(entity, mesh);
        m_Scenario->AddComponent<Shader>(entity, shaderID);
        m_Scenario->AddComponent<Texture>(entity);
        m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {x, y, z}, .Rotation = {0, 0, 0}, .Scale = {1, 1, 1}});
    }
};