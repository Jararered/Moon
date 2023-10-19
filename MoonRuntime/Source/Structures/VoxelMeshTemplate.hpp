#pragma once

#include "MeshInterface.hpp"
#include "VoxelBuffer.hpp"

#include <memory>

struct VoxelMeshTemplate : public MeshInterface
{
    VoxelMeshTemplate() = default;
    ~VoxelMeshTemplate() override = default;

    void Draw() override
    {
        Buffer->Bind();
        Buffer->Draw();
        Buffer->Unbind();
    }

    std::shared_ptr<VoxelBuffer> Buffer;
};