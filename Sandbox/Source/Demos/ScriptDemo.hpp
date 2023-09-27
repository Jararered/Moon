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
        const auto texture = Texture("Textures/debug.png");
        const auto script1 = std::make_shared<RotateScript>(0.1f);
        const auto script2 = std::make_shared<RotateScript>(1.0f);
        const auto script3 = std::make_shared<RotateScript>(10.0f);

        m_AvaliableMeshesMap.emplace("Cube", cube);

        m_AvaliableScriptsMap.emplace("Rotate Slow", script1);
        m_AvaliableScriptsMap.emplace("Rotate", script2);
        m_AvaliableScriptsMap.emplace("Rotate Fast", script3);

        m_AvaliableTexturesMap.emplace("debug.png", texture);

        const auto staticShader = Shader("Shaders/PositionNormalTexture.vert", "Shaders/PositionNormalTexture.frag");

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
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {-5.0f, 2.0f, 0.0f}, .Rotation = {0, 0, 0}, .Scale = {3, 3, 3}});
            e_Scenario.AddComponent<RigidBody>(entity);
            e_Scenario.AddComponent<Script>(entity, script1);
        }
        // Cube with Script
        {
            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, cube);
            e_Scenario.AddComponent<Shader>(entity, staticShader);
            e_Scenario.AddComponent<Texture>(entity, texture);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {0.0f, 1.5f, 0.0f}, .Rotation = {0, 0, 0}, .Scale = {2, 2, 2}});
            e_Scenario.AddComponent<RigidBody>(entity);
            e_Scenario.AddComponent<Script>(entity, script2);
        }
        // Cube with Script
        {
            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, cube);
            e_Scenario.AddComponent<Shader>(entity, staticShader);
            e_Scenario.AddComponent<Texture>(entity, texture);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {3.5f, 1.0f, 0.0f}, .Rotation = {0, 0, 0}, .Scale = {1, 1, 1}});
            e_Scenario.AddComponent<RigidBody>(entity);
            e_Scenario.AddComponent<Script>(entity, script3);
        }
    }
};
