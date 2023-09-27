#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"

#include "Scripts/Rotation.hpp"

extern Scenario e_Scenario;

class EntityCreationDemo final : public Engine
{
public:
    void CreateScene()
    {
        m_AvaliableMeshesMap.emplace("Cube", std::make_shared<TexturedCubeMesh>());

        m_AvaliableScriptsMap.emplace("Rotate Slow", std::make_shared<RotateScript>(0.1f));
        m_AvaliableScriptsMap.emplace("Rotate", std::make_shared<RotateScript>(1.0f));
        m_AvaliableScriptsMap.emplace("Rotate Fast", std::make_shared<RotateScript>(10.0f));

        m_AvaliableTexturesMap.emplace("Debug", Texture("Textures/debug.png"));
        m_AvaliableTexturesMap.emplace("Circle", Texture("Textures/circle.png"));

        m_AvaliableShadersMap.emplace("Simple", Shader("Shaders/PositionNormalTexture.vert", "Shaders/PositionNormalTexture.frag"));

        // Floor
        {
            const Entity entity = e_Scenario.CreateEntity();
            e_Scenario.AddComponent<Mesh>(entity, m_AvaliableMeshesMap["Cube"]);
            e_Scenario.AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
            e_Scenario.AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug"]);
            e_Scenario.AddComponent<Transform>(entity, Transform{.Position = {0, 0, 0}, .Rotation = {0, 0, 0}, .Scale = {20, 1, 20}});
            e_Scenario.AddComponent<RigidBody>(entity);
        }
    }
};
