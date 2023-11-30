#pragma once

namespace Moon
{

    struct MeshInterface
    {
        virtual ~MeshInterface() = default;

        virtual void Draw() = 0;
    };

}