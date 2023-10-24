#pragma once

#include <Moon.hpp>

#include "Mesh/Cube.hpp"
#include "Mesh/SingleVoxel.hpp"
#include "Script/TestScript.hpp"

class Editor final : public Moon::Engine
{
public:
    void CreateScene()
    {
        m_AvaliableMeshesMap.emplace("Cube", std::make_shared<TexturedCubeMesh>());
        m_AvaliableMeshesMap.emplace("Voxel", std::make_shared<SingleVoxel>());

        m_AvaliableTexturesMap.emplace("Checker 32x32", Texture("Textures/checker.png"));
        m_AvaliableTexturesMap.emplace("Debug 32x32", Texture("Textures/debug.png"));

        m_AvaliableShadersMap.emplace("Simple", Shader("Shaders/PositionNormalTexture.vert", "Shaders/Texture.frag"));
        m_AvaliableShadersMap.emplace("White", Shader("Shaders/PositionNormalTexture.vert", "Shaders/White.frag"));
        m_AvaliableShadersMap.emplace("Voxel", Shader("Shaders/Voxel.vert", "Shaders/Voxel.geom", "Shaders/Voxel.frag"));

        m_AvaliableScriptsMap.emplace("Test Script", std::make_shared<TestScript>());

        CreateBase();

        {
            Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Mesh>(entity, m_AvaliableMeshesMap["Cube"]);
            m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["White"]);
            m_Scenario->AddComponent<Transform>(entity, Transform{{0, 2, 0}, {0, 0, 0}, {1, 1, 1}});
            m_Scenario->AddComponent<RigidBody>(entity);
        }
    }

    void CreateBase()
    {
        const auto length = 21.0f;
        const auto width = 21.0f;

        // Floor
        {
            Entity entity = m_Scenario->CreateEntity();
            m_Scenario->AddComponent<Shader>(entity, m_AvaliableShadersMap["Simple"]);
            m_Scenario->AddComponent<Texture>(entity, m_AvaliableTexturesMap["Debug 32x32"]);
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
