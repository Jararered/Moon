#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"

#include "Scripts/Rotation.hpp"

class EntityCreationDemo final : public Engine
{
public:
    void CreateScene()
    {
        m_AvaliableMeshesMap.emplace("Cube", std::make_shared<TexturedCubeMesh>());

        m_AvaliableScriptsMap.emplace("Rotate Slow", std::make_shared<RotateScript>(0.1f));
        m_AvaliableScriptsMap.emplace("Rotate", std::make_shared<RotateScript>(1.0f));
        m_AvaliableScriptsMap.emplace("Rotate Fast", std::make_shared<RotateScript>(10.0f));

        m_AvaliableTexturesMap.emplace("Debug 32x32", Texture("Textures/debug32.png"));
        m_AvaliableTexturesMap.emplace("Debug 64x64", Texture("Textures/debug64.png"));
        m_AvaliableTexturesMap.emplace("Mud", Texture("Textures/mud.png"));
        m_AvaliableTexturesMap.emplace("Grass", Texture("Textures/grass.png"));

        m_AvaliableShadersMap.emplace("Simple", Shader("Shaders/PositionNormalTexture.vert", "Shaders/PositionNormalTexture.frag"));

        // Floor
        {
            const Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Mesh>(entity, m_AvaliableMeshesMap["Cube"]);
            m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
            m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug 32x32"]);
            m_Scenario->AddComponent<Transform>(entity, Transform{.Position = {0, -1, 0}, .Rotation = {0, 0, 0}, .Scale = {20, 1, 20}});
            m_Scenario->AddComponent<RigidBody>(entity);
        }
    }
};