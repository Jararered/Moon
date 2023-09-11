#pragma once

#include "Vertex.hpp"
#include "VertexBuffer.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <memory>

class MeshInterface
{
public:
    MeshInterface() = default;
    MeshInterface(const MeshInterface&) = default;
    MeshInterface(MeshInterface&&) = default;
    MeshInterface& operator=(const MeshInterface&) = default;
    MeshInterface& operator=(MeshInterface&&) = default;
    virtual ~MeshInterface() = default;

    virtual void Draw() = 0;
};

template <typename VertexType> struct MeshTemplate : public MeshInterface
{
public:
    MeshTemplate() = default;
    MeshTemplate(const MeshTemplate&) = default;
    MeshTemplate(MeshTemplate&&) = default;
    MeshTemplate& operator=(const MeshTemplate&) = default;
    MeshTemplate& operator=(MeshTemplate&&) = default;
    ~MeshTemplate() override = default;

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
    std::shared_ptr<MeshInterface> Data;
};