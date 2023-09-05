#pragma once

struct WindowSpecification
{
    enum GraphicsAPI
    {
        OpenGL,
        Vulkan,
        Metal
    };

    GraphicsAPI API = GraphicsAPI::OpenGL;
    float Width = 1280;
    float Height = 720;
    bool VSync = true;
    bool EnableImgui = false;
};