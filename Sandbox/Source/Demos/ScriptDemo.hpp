#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"

#include "Scripts/Rotation.hpp"

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
            const Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Mesh>(entity, cube);
            m_Scenario->AddComponent<Shader>(entity, staticShader);
            m_Scenario->AddComponent<Texture>(entity, texture);
            m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {0, 0, 0}, .Rotation = {0, 0, 0}, .Scale = {20, 1, 20}});
            m_Scenario->AddComponent<RigidBody>(entity);
        }

        // Cube with Script
        {
            const Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Mesh>(entity, cube);
            m_Scenario->AddComponent<Shader>(entity, staticShader);
            m_Scenario->AddComponent<Texture>(entity, texture);
            m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {-5.0f, 2.0f, 0.0f}, .Rotation = {0, 0, 0}, .Scale = {3, 3, 3}});
            m_Scenario->AddComponent<RigidBody>(entity);
            m_Scenario->AddComponent<Script>(entity, script1);
        }
        // Cube with Script
        {
            const Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Mesh>(entity, cube);
            m_Scenario->AddComponent<Shader>(entity, staticShader);
            m_Scenario->AddComponent<Texture>(entity, texture);
            m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {0.0f, 1.5f, 0.0f}, .Rotation = {0, 0, 0}, .Scale = {2, 2, 2}});
            m_Scenario->AddComponent<RigidBody>(entity);
            m_Scenario->AddComponent<Script>(entity, script2);
        }
        // Cube with Script
        {
            const Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Mesh>(entity, cube);
            m_Scenario->AddComponent<Shader>(entity, staticShader);
            m_Scenario->AddComponent<Texture>(entity, texture);
            m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {3.5f, 1.0f, 0.0f}, .Rotation = {0, 0, 0}, .Scale = {1, 1, 1}});
            m_Scenario->AddComponent<RigidBody>(entity);
            m_Scenario->AddComponent<Script>(entity, script3);
        }
    }
};
