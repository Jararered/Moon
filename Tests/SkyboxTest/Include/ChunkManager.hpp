#pragma once

#include <iostream>
#include <unordered_map>

class ChunkManager
{
public:
    ChunkManager()
    {
        std::cout << "ChunkManager::ChunkManager()" << "\n";
    }
    ~ChunkManager() = default;

    static void AddToLoadedChunks(glm::ivec3 index)
    {

    }
    static std::vector<glm::ivec3> m_LoadedChunks;
};