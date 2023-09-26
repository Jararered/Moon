#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"

extern Scenario e_Scenario;

class SceneDemo final : public Engine
{
public:
    void CreateScene()
    {
        const unsigned int count = 9999;

        const auto mesh = std::make_shared<TexturedCubeMesh>();
        const auto shaderID = Shader("Shaders/PositionNormalTexture.vert", "Shaders/White.frag");

        const Entity entity = e_Scenario.CreateEntity();
        e_Scenario.AddComponent<Mesh>(entity, mesh);
        e_Scenario.AddComponent<Shader>(entity, shaderID);
        e_Scenario.AddComponent<Texture>(entity);
        e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {x, y, z}, .Rotation = {0, 0, 0}, .Scale = {1, 1on, 1}});
    }
};