#pragma once

#include <Moon.hpp>

#include "Mesh/Cube.hpp"
#include "Mesh/VoxelChunk.hpp"
#include "Mesh/VoxelSingle.hpp"
#include "Script/TestScript.hpp"

#include "Panel/StatisticsPanel.hpp"

class Editor final : public Moon::Application
{
public:
    void LoadResources()
    {
        m_MeshLibrary.emplace("Cube", std::make_shared<TexturedCubeMesh>());
        m_MeshLibrary.emplace("Voxel Single", std::make_shared<VoxelSingle>());
        m_MeshLibrary.emplace("Voxel Chunk", std::make_shared<VoxelChunk>(16));

        m_TextureLibrary.emplace("Checker 32x32", Texture("Texture/checker.png"));
        m_TextureLibrary.emplace("Debug 32x32", Texture("Texture/debug.png"));

        m_ShaderLibrary.emplace("Simple", Shader("Shader/PositionNormalTexture.vert", "Shader/Texture.frag"));
        m_ShaderLibrary.emplace("White", Shader("Shader/PositionNormalTexture.vert", "Shader/White.frag"));
        m_ShaderLibrary.emplace("Voxel", Shader("Shader/Voxel.vert", "Shader/Voxel.geom", "Shader/Voxel.frag"));

        // m_ScriptLibrary.emplace("Test Script", std::make_shared<TestScript>());
    }

    void CreatePanels() { m_Panels.emplace("Statistics", std::make_shared<StatisticsPanel>()); }
};
