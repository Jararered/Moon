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

        // Floor
        {
            Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Mesh>(entity, m_AvaliableMeshesMap["Cube"]);
            m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
            m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug 32x32"]);
            m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {0, -1, 0}, .Rotation = {0, 0, 0}, .Scale = {20, 1, 20}});
            m_Scenario->AddComponent<RigidBody>(entity);
        }

        // Cube 1
        {
            Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Mesh>(entity, m_AvaliableMeshesMap["Cube"]);
            m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
            m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug 32x32"]);
            m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {10, 1, 0}, .Rotation = {0, 0, 0}, .Scale = {1, 1, 1}});
            m_Scenario->AddComponent<RigidBody>(entity, RigidBody{.Velocity = {-25, 0, 0}, .Acceleration = {0, 0, 0}, .Mass = 1});
        }

        // Cube 2
        {
            Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Mesh>(entity, m_AvaliableMeshesMap["Cube"]);
            m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
            m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug 32x32"]);
            m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {0, 0, 0}, .Rotation = {0, 0, 0}, .Scale = {1, 1, 1}});
            m_Scenario->AddComponent<RigidBody>(entity, RigidBody{.Velocity = {0, 0, 0}, .Acceleration = {0, 0, 0}, .Mass = 1});
        }
    }
};
