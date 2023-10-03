#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"

class PhysicsDemo final : public Engine
{
public:
    void CreateScene()
    {
        m_AvaliableMeshesMap.emplace("Cube", std::make_shared<TexturedCubeMesh>());
        m_AvaliableTexturesMap.emplace("Debug 32x32", Texture("Textures/debug32.png"));
        m_AvaliableTexturesMap.emplace("Debug 64x64", Texture("Textures/debug64.png"));
        m_AvaliableTexturesMap.emplace("Mud", Texture("Textures/mud.png"));
        m_AvaliableTexturesMap.emplace("Grass", Texture("Textures/grass.png"));
        m_AvaliableShadersMap.emplace("Simple", Shader("Shaders/PositionNormalTexture.vert", "Shaders/PositionNormalTexture.frag"));

        CreateBase();
        // CreatePillars();
    }

    void CreateBase()
    {
        // Floor
        {
            Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Mesh>(entity, m_AvaliableMeshesMap["Cube"]);
            m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
            m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug 32x32"]);
            m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {0, -1, 0}, .Rotation = {0, 0, 0}, .Scale = {20, 1, 20}});
            m_Scenario->AddComponent<RigidBody>(entity);
        }

        // Walls
        {
            Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Mesh>(entity, m_AvaliableMeshesMap["Cube"]);
            m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
            m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug 32x32"]);
            m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {10, 0, 0}, .Rotation = {0, 0, 0}, .Scale = {1, 1, 20}});
            m_Scenario->AddComponent<RigidBody>(entity);
        }
        {
            Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Mesh>(entity, m_AvaliableMeshesMap["Cube"]);
            m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
            m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug 32x32"]);
            m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {-10, 0, 0}, .Rotation = {0, 0, 0}, .Scale = {1, 1, 20}});
            m_Scenario->AddComponent<RigidBody>(entity);
        }
        {
            Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Mesh>(entity, m_AvaliableMeshesMap["Cube"]);
            m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
            m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug 32x32"]);
            m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {0, 0, 10}, .Rotation = {0, 0, 0}, .Scale = {20, 1, 1}});
            m_Scenario->AddComponent<RigidBody>(entity);
        }
        {
            Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Mesh>(entity, m_AvaliableMeshesMap["Cube"]);
            m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
            m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug 32x32"]);
            m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {0, 0, -10}, .Rotation = {0, 0, 0}, .Scale = {20, 1, 1}});
            m_Scenario->AddComponent<RigidBody>(entity);
        }
    }

    void CreatePillars()
    {
        int offset = -8;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                Entity entity = m_Scenario->CreateEntity();

                const auto y = Random::Value<float>(1.0f, 5.0f);
                m_Scenario->AddComponent<Mesh>(entity, m_AvaliableMeshesMap["Cube"]);
                m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
                m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug 32x32"]);
                m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {2 * i + offset, y * 0.5f - 0.5f, 2 * j + offset}, .Rotation = {0, 0, 0}, .Scale = {1, y, 1}});
                m_Scenario->AddComponent<RigidBody>(entity);
            }
        }
    }
};
