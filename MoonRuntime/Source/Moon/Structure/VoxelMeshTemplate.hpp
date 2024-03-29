#pragma once

#include "MeshInterface.hpp"
#include "VoxelBuffer.hpp"

#include <memory>

namespace Moon
{

    struct VoxelMeshTemplate : public MeshInterface
    {
        VoxelMeshTemplate() { Buffer = std::make_shared<VoxelBuffer>(); }
        ~VoxelMeshTemplate() override = default;

        void Draw() override
        {
            Buffer->Bind();
            Buffer->Draw();
            Buffer->Unbind();
        }

        std::shared_ptr<VoxelBuffer> Buffer;
    };

}