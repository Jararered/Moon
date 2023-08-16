#pragma once

#include "Vertex.hpp"
#include "VertexBuffer.hpp"

struct MeshBase
{
    MeshBase() = default;
    virtual ~MeshBase() = default;

    virtual void Draw() = 0;
};

template <typename VertexType> struct TMeshComponent : public MeshBase
{
    void Draw() override
    {
        VertexBuffer.Bind();
        VertexBuffer.Draw();
        VertexBuffer.Unbind();
    }

    VertexBuffer<VertexType> VertexBuffer;
};

struct Mesh
{
    MeshBase* p_Mesh = nullptr;
};