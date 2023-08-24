#pragma once

#include "Vertex.hpp"
#include "VertexBuffer.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <memory>

struct DrawableMesh
{
    DrawableMesh() = default;
    virtual ~DrawableMesh() = default;

    virtual void Draw() = 0;
};

template <typename VertexType> struct TMeshComponent : public DrawableMesh
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
    std::shared_ptr<DrawableMesh> Data;
};