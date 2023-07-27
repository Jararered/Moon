#pragma once

struct WindowSpecification
{
    enum GraphicsAPI
    {
        OpenGL,
        Vulkan,
        Metal
    };

    GraphicsAPI API;
    int Width;
    int Height;
    bool VSync;
};