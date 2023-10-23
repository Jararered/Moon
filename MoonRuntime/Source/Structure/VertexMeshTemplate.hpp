#pragma once

#include "MeshInterface.hpp"
#include "VertexBuffer.hpp"

#include <memory>

template <typename T> struct VertexMeshTemplate : public MeshInterface
{
    VertexMeshTemplate() { Buffer = std::make_shared<VertexBuffer<T>>(); }
    ~VertexMeshTemplate() override = default;

    void Draw() override
    {
        Buffer->Bind();
        Buffer->Draw();
        Buffer->Unbind();
    }

    std::shared_ptr<VertexBuffer<T>> Buffer;
};