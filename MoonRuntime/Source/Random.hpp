#pragma once

#include <FastNoiseLite.h>

class Random
{
public:
    static FastNoiseLite s_Noise1D;
    static FastNoiseLite s_Noise2D;
    static FastNoiseLite s_Noise3D;
};
