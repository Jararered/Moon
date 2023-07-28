#pragma once

#include <FastNoiseLite.h>

class ChunkGenerator
{
public:
    static ChunkGenerator& Get()
    {
        static ChunkGenerator s_Instance;
        return s_Instance;
    }

    static void Initialize()
    {
        Get().Noise3D.SetFrequency(0.05f);
    }

    static float Get3DNoise(int x, int y, int z) { return Get().Noise3D.GetNoise(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)); }

    static int GetSeed() { return Get().Seed; }
    static void SetSeed(int seed)
    {
        Get().Seed = seed;
        Get().Noise3D.SetSeed(seed);
    }

private:
    ChunkGenerator() {}
    ChunkGenerator(ChunkGenerator const&);
    void operator=(ChunkGenerator const&);

    int Seed = 0;
    FastNoiseLite Noise3D;
};
