#pragma once

struct MeshInterface
{
    virtual ~MeshInterface() = default;

    virtual void Draw() = 0;
};