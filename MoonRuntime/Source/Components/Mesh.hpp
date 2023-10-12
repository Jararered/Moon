#pragma once

#include "Vertex.hpp"
#include "VertexBuffer.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <memory>

struct MeshInterface
{
    virtual ~MeshInterface() = default;

    virtual void Draw() = 0;
};

template <typename T> struct MeshTemplate : public MeshInterface
{
    ~MeshTemplate() override = default;

    void Draw() override
    {
        VertexBuffer.Bind();
        VertexBuffer.Draw();
        VertexBuffer.Unbind();
    }

    VertexBuffer<T> VertexBuffer;
};

typedef std::shared_ptr<MeshInterface> Mesh;