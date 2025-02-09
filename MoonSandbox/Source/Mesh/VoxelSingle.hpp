#pragma once

#include "Structure/VoxelMeshTemplate.hpp"

class VoxelSingle : public Moon::VoxelMeshTemplate
{
public:
    VoxelSingle(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f))
    {
        auto& voxels = Buffer->GetData();

        voxels.emplace_back(position);

        Buffer->BufferData();
    }
};