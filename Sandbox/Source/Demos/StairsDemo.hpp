#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"

extern Scenario e_Scenario;

class StairsDemo final : public Engine
{
public:
    void CreateScene()
    {
        const auto cube = std::make_shared<TexturedCubeMesh>();
        const auto staticShader = Shader("Shaders/PositionNormalTexture.vert", "Shaders/Normal.frag");

        // Floor
        {
            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, cube);
            e_Scenario.AddComponent<Shader>(entity, staticShader);
            e_Scenario.AddComponent<Texture>(entity);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {0, 0, 0}, .Rotation = {0, 0, 0}, .Scale = {20, 1, 20}});
            e_Scenario.AddComponent<RigidBody>(entity);
        }

        const auto normal = Shader("Shaders/PositionNormalTexture.vert", "Shaders/Normal.frag");
        for (float x = 0.6f; x < 10.0f; x += 0.2f)
        {
            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, cube);
            e_Scenario.AddComponent<Shader>(entity, normal);
            e_Scenario.AddComponent<Texture>(entity);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {0, x, -x}, .Rotation = {0, 0, 0}, .Scale = {1.0f, 0.2f, 0.2f}});
            e_Scenario.AddComponent<RigidBody>(entity, RigidBody{.Velocity{0, 0, 0}, .Acceleration{0, 0, 0}, .Mass = 0.0f});
        }
    }
};