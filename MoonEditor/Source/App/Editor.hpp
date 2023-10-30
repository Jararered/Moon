#pragma once

#include <Moon.hpp>

#include "Mesh/Cube.hpp"
#include "Mesh/VoxelChunk.hpp"
#include "Mesh/VoxelSingle.hpp"
#include "Script/TestScript.hpp"

class Editor final : public Moon::Application
{
public:
    void CreateScene()
    {
        using namespace Moon;

        m_AvaliableMeshesMap.emplace("Cube", std::make_shared<TexturedCubeMesh>());
        m_AvaliableMeshesMap.emplace("VoxelSingle", std::make_shared<VoxelSingle>());
        m_AvaliableMeshesMap.emplace("VoxelChunk", std::make_shared<VoxelChunk>(16));

        m_AvaliableTexturesMap.emplace("Checker 32x32", Texture("Texture/checker.png"));
        m_AvaliableTexturesMap.emplace("Debug 32x32", Texture("Texture/debug.png"));

        m_AvaliableShadersMap.emplace("Simple", Shader("Shader/PositionNormalTexture.vert", "Shader/Texture.frag"));
        m_AvaliableShadersMap.emplace("White", Shader("Shader/PositionNormalTexture.vert", "Shader/White.frag"));
        m_AvaliableShadersMap.emplace("Voxel", Shader("Shader/Voxel.vert", "Shader/Voxel.geom", "Shader/Voxel.frag"));

        m_AvaliableScriptsMap.emplace("Test Script", std::make_shared<TestScript>());

        CreateBase();

        // Voxel Test
        // {
        //     Moon::Entity entity(m_Scenario);
        //     entity.AddComponent<Mesh>(m_AvaliableMeshesMap.at("VoxelSingle"));
        //     entity.AddComponent<Shader>(m_AvaliableShadersMap.at("Voxel"));
        //     entity.AddComponent<Transform>(Transform{{0, 2, 0}, {0, 0, 0}, {1, 1, 1}});
        // }

        {
            Moon::Entity entity(m_Scenario);
            entity.AddComponent<Mesh>(m_AvaliableMeshesMap.at("VoxelChunk"));
            entity.AddComponent<Shader>(m_AvaliableShadersMap.at("Voxel"));
            entity.AddComponent<Transform>(Transform{{0, 2, 0}, {0, 0, 0}, {1, 1, 1}});
        }
    }

    void CreateBase()
    {
        using namespace Moon;

        const auto length = 21.0f;
        const auto width = 21.0f;

        // Floor
        {
            Moon::Entity entity(m_Scenario);
            entity.AddComponent<Shader>(m_AvaliableShadersMap["Simple"]);
            entity.AddComponent<Texture>(m_AvaliableTexturesMap["Debug 32x32"]);
            entity.AddComponent<Transform>(Transform{{0, -1, 0}, {0, 0, 0}, {length, 1, width}});
            entity.AddComponent<Mesh>(std::make_shared<TexturedCubeMesh>(glm::vec3(length, 1, width)));
            entity.AddComponent<RigidBody>();
        }

        // Walls
        {
            Moon::Entity entity(m_Scenario);
            entity.AddComponent<Shader>(m_AvaliableShadersMap["Simple"]);
            entity.AddComponent<Texture>(m_AvaliableTexturesMap["Debug 32x32"]);
            entity.AddComponent<Transform>(Transform{{length / 2.0f + 0.5f, 0, 0}, {0, 0, 0}, {1, 1, width}});
            entity.AddComponent<Mesh>(std::make_shared<TexturedCubeMesh>(glm::vec3(1, 1, width)));
            entity.AddComponent<RigidBody>();
        }
        {
            Moon::Entity entity(m_Scenario);
            entity.AddComponent<Shader>(m_AvaliableShadersMap["Simple"]);
            entity.AddComponent<Texture>(m_AvaliableTexturesMap["Debug 32x32"]);
            entity.AddComponent<Transform>(Transform{{-length / 2.0f - 0.5f, 0, 0}, {0, 0, 0}, {1, 1, width}});
            entity.AddComponent<Mesh>(std::make_shared<TexturedCubeMesh>(glm::vec3(1, 1, width)));
            entity.AddComponent<RigidBody>();
        }
        {
            Moon::Entity entity(m_Scenario);
            entity.AddComponent<Shader>(m_AvaliableShadersMap["Simple"]);
            entity.AddComponent<Texture>(m_AvaliableTexturesMap["Debug 32x32"]);
            entity.AddComponent<Transform>(Transform{{0, 0, width / 2.0f + 0.5f}, {0, 0, 0}, {length, 1, 1}});
            entity.AddComponent<Mesh>(std::make_shared<TexturedCubeMesh>(glm::vec3(length, 1, 1)));
            entity.AddComponent<RigidBody>();
        }
        {
            Moon::Entity entity(m_Scenario);
            entity.AddComponent<Shader>(m_AvaliableShadersMap["Simple"]);
            entity.AddComponent<Texture>(m_AvaliableTexturesMap["Debug 32x32"]);
            entity.AddComponent<Transform>(Transform{{0, 0, -width / 2.0f - 0.5f}, {0, 0, 0}, {length, 1, 1}});
            entity.AddComponent<Mesh>(std::make_shared<TexturedCubeMesh>(glm::vec3(length, 1, 1)));
            entity.AddComponent<RigidBody>();
        }
    }

    void CreatePillars()
    {
        using namespace Moon;

        float offset = -9.0f;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                UUID entity = m_Scenario->CreateEntity();

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
