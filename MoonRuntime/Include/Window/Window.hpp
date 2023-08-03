#pragma once

#include "Renderer.hpp"

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

class Window
{
public:
    Window(const WindowSpecification& spec){};
    virtual ~Window(){};

    virtual void Update(float dt) = 0;
    virtual bool IsRunning() = 0;
    virtual Renderer* CreateRenderer() = 0;

    WindowSpecification m_WindowSpecification;
};