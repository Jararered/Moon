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
        m_AvaliableMeshesMap.emplace("Voxel Single", std::make_shared<VoxelSingle>());
        m_AvaliableMeshesMap.emplace("Voxel Chunk", std::make_shared<VoxelChunk>(16));

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
            entity.AddComponent<Mesh>(m_AvaliableMeshesMap.at("Voxel Chunk"));
            entity.AddComponent<Shader>(m_AvaliableShadersMap.at("Voxel"));
            entity.AddComponent<Transform>(Transform{{0, 2, 0}, {0, 0, 0}, {1, 1, 1}});
        }
    }

    void CreateBase()
    {
        using namespace Moon;

        const auto length = 20.0f;
        const auto width = 20.0f;

        {
            Entity entity(m_Scenario);
            entity.AddComponent<Shader>(m_AvaliableShadersMap["Simple"]);
            entity.AddComponent<Texture>(m_AvaliableTexturesMap["Debug 32x32"]);
            entity.AddComponent<Transform>(Transform{{0, -1, 0}, {0, 0, 0}, {length, 1, width}});
            entity.AddComponent<Mesh>(std::make_shared<TexturedCubeMesh>(glm::vec3(length, 1, width)));
            entity.AddComponent<RigidBody>();
        }
    }
};
