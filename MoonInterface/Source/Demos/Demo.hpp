#pragma once

#include <Moon.hpp>

#include "Meshes/Cube.hpp"
#include "Scripts/Rotation.hpp"
#include "Scripts/TestScript.hpp"

class Demo final : public Moon::Engine
{
public:
    void CreateScene()
    {
        m_AvaliableMeshesMap.emplace("Cube", std::make_shared<TexturedCubeMesh>());
        m_AvaliableTexturesMap.emplace("Checker 8x8", Texture("Textures/checker8.png"));
        m_AvaliableTexturesMap.emplace("Checker 16x16", Texture("Textures/checker16.png"));
        m_AvaliableTexturesMap.emplace("Checker 32x32", Texture("Textures/checker32.png"));
        m_AvaliableTexturesMap.emplace("Debug 32x32", Texture("Textures/debug32.png"));
        m_AvaliableTexturesMap.emplace("Debug 64x64", Texture("Textures/debug64.png"));
        m_AvaliableTexturesMap.emplace("Mud", Texture("Textures/mud.png"));
        m_AvaliableTexturesMap.emplace("Grass", Texture("Textures/grass.png"));
        m_AvaliableShadersMap.emplace("Simple", Shader("Shaders/PositionNormalTexture.vert", "Shaders/PositionNormalTexture.frag"));
        m_AvaliableScriptsMap.emplace("Rotate", std::make_shared<RotateScript>(1.0f));
        m_AvaliableScriptsMap.emplace("Test Script", std::make_shared<TestScript>());

        CreateBase();
        CreatePillars();
    }

    void CreateBase()
    {
        const auto length = 21.0f;
        const auto width = 21.0f;

        // Floor
        {
            Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
            m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Checker 8x8"]);
            m_Scenario->AddComponent<Transform>(entity, Transform{{0, -1, 0}, {0, 0, 0}, {length, 1, width}});
            m_Scenario->AddComponent<Mesh>(entity, std::make_shared<TexturedCubeMesh>(glm::vec3(length, 1, width)));
            m_Scenario->AddComponent<RigidBody>(entity);
        }

        // Walls
        {
            Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
            m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug 32x32"]);
            m_Scenario->AddComponent<Transform>(entity, Transform{{length / 2.0f + 0.5f, 0, 0}, {0, 0, 0}, {1, 1, width}});
            m_Scenario->AddComponent<Mesh>(entity, std::make_shared<TexturedCubeMesh>(glm::vec3(1, 1, width)));
            m_Scenario->AddComponent<RigidBody>(entity);
        }
        {
            Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
            m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug 32x32"]);
            m_Scenario->AddComponent<Transform>(entity, Transform{{-length / 2.0f - 0.5f, 0, 0}, {0, 0, 0}, {1, 1, width}});
            m_Scenario->AddComponent<Mesh>(entity, std::make_shared<TexturedCubeMesh>(glm::vec3(1, 1, width)));
            m_Scenario->AddComponent<RigidBody>(entity);
        }
        {
            Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
            m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug 32x32"]);
            m_Scenario->AddComponent<Transform>(entity, Transform{{0, 0, width / 2.0f + 0.5f}, {0, 0, 0}, {length, 1, 1}});
            m_Scenario->AddComponent<Mesh>(entity, std::make_shared<TexturedCubeMesh>(glm::vec3(length, 1, 1)));
            m_Scenario->AddComponent<RigidBody>(entity);
        }
        {
            Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
            m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug 32x32"]);
            m_Scenario->AddComponent<Transform>(entity, Transform{{0, 0, -width / 2.0f - 0.5f}, {0, 0, 0}, {length, 1, 1}});
            m_Scenario->AddComponent<Mesh>(entity, std::make_shared<TexturedCubeMesh>(glm::vec3(length, 1, 1)));
            m_Scenario->AddComponent<RigidBody>(entity);
        }
    }

    void CreatePillars()
    {
        float offset = -9.0f;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                Entity entity = m_Scenario->CreateEntity();

                const auto y = glm::floor(Random::Value<float>(1.0f, 5.0f));
                m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
                m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug 32x32"]);
                m_Scenario->AddComponent<Transform>(entity, Transform{{2 * i + offset, y * 0.5f - 0.5f, 2 * j + offset}, {0, 0, 0}, {1, y, 1}});
                m_Scenario->AddComponent<Mesh>(entity, std::make_shared<TexturedCubeMesh>(glm::vec3(1, y, 1)));
                m_Scenario->AddComponent<RigidBody>(entity);
            }
        }
    }
};