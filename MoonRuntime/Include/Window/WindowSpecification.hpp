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
    float Width;
    float Height;
    bool VSync;
};