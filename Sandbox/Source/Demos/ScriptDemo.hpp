#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"

#include "Scripts/Rotation.hpp"

extern Scenario e_Scenario;

class ScriptDemo final : public Engine
{
public:
    void CreateScene()
    {
        const auto cube = std::make_shared<TexturedCubeMesh>();
        const auto staticShader = Shader("Shaders/PositionNormalTexture.vert", "Shaders/PositionNormalTexture.frag");
        const auto texture = Texture("Textures/checker.png");
        const auto script1 = std::make_shared<RotateScript>(0.1f);
        const auto script2 = std::make_shared<RotateScript>(1.0f);
        const auto script3 = std::make_shared<RotateScript>(10.0f);

        // Floor
        {
            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, cube);
            e_Scenario.AddComponent<Shader>(entity, staticShader);
            e_Scenario.AddComponent<Texture>(entity, texture);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {0, 0, 0}, .Rotation = {0, 0, 0}, .Scale = {20, 1, 20}});
            e_Scenario.AddComponent<RigidBody>(entity);
        }

        // Cube with Script
        {
            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, cube);
            e_Scenario.AddComponent<Shader>(entity, staticShader);
            e_Scenario.AddComponent<Texture>(entity, texture);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {-2, 1, 0}});
            e_Scenario.AddComponent<RigidBody>(entity);
            e_Scenario.AddComponent<Script>(entity, script1);
        }
        // Cube with Script
        {
            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, cube);
            e_Scenario.AddComponent<Shader>(entity, staticShader);
            e_Scenario.AddComponent<Texture>(entity, texture);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {0, 1, 0}});
            e_Scenario.AddComponent<RigidBody>(entity);
            e_Scenario.AddComponent<Script>(entity, script2);
        }
        // Cube with Script
        {
            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, cube);
            e_Scenario.AddComponent<Shader>(entity, staticShader);
            e_Scenario.AddComponent<Texture>(entity, texture);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {2, 1, 0}});
            e_Scenario.AddComponent<RigidBody>(entity);
            e_Scenario.AddComponent<Script>(entity, script3);
        }
    }
};
