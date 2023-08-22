#pragma once

#include "Vertex.hpp"
#include "VertexBuffer.hpp"

struct TMeshBase
{
    TMeshBase() = default;
    virtual ~TMeshBase() = default;

    virtual void Draw() = 0;
};

template <typename VertexType> struct TMeshComponent : public TMeshBase
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
    TMeshBase* p_Mesh = nullptr;
};