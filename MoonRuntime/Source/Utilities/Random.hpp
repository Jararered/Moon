#pragma once

#include <FastNoiseLite.h>

class Random
{
public:
    static FastNoiseLite s_Noise1D;
    static FastNoiseLite s_Noise2D;
    static FastNoiseLite s_Noise3D;

    template <typename T> static T Value(T min, T max)
    {
        // 0 to 1
        const T value = static_cast<T>(rand()) / static_cast<T>(RAND_MAX);
        const T result = min + value * (max - min);
        return result;
    }
};
