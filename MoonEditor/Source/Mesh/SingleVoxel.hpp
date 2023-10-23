#pragma once

#include "Structure/VoxelMeshTemplate.hpp"

class SingleVoxel : public VoxelMeshTemplate
{
public:
    SingleVoxel() = default;
    SingleVoxel(const glm::vec3& position)
    {
        auto& voxels = Buffer->GetData();

        voxels.emplace_back(position);

        Buffer->BufferData();
    }
};