#pragma once

#include "Structure/VoxelMeshTemplate.hpp"

#include "octree/octree.h"

class VoxelChunk : public Moon::VoxelMeshTemplate
{
public:
    VoxelChunk(int size = 2) : m_Size(size)
    {
        Generate();
        Render();
    }

    void Generate()
    {
        m_Data = Octree<unsigned char>(m_Size);

        for (int z = 0; z < m_Size; z++)
        {
            for (int y = 0; y < m_Size; y++)
            {
                for (int x = 0; x < m_Size; x++)
                {
                    m_Data(x, y, z) = 1;
                }
            }
        }
    }

    void Render()
    {
        auto& voxels = Buffer->GetData();
        voxels.reserve(m_Size * m_Size * m_Size);

        for (int z = 0; z < m_Size; z++)
        {
            for (int y = 0; y < m_Size; y++)
            {
                for (int x = 0; x < m_Size; x++)
                {
                    if (IsBlock(x + 1, y, z) and IsBlock(x - 1, y, z) and IsBlock(x, y + 1, z) and IsBlock(x, y - 1, z) and IsBlock(x, y, z + 1) and IsBlock(x, y, z - 1))
                        continue;

                    voxels.emplace_back(glm::vec3(x, y, z));
                }
            }
        }

        Buffer->BufferData();
    }

    bool IsBlock(int x, int y, int z)
    {
        if (x < 0 or y < 0 or z < 0 or x > m_Size - 1 or y > m_Size - 1 or z > m_Size - 1)
            return false;

        return m_Data(x, y, z);
    }

private:
    Octree<unsigned char> m_Data = Octree<unsigned char>(0);
    int m_Size;
};