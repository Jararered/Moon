#pragma once

#include "Renderer.hpp"
#include "WindowSpecification.hpp"

class Window
{
public:
    Window(const WindowSpecification& spec) {};
    virtual ~Window() {};

    virtual void Update(float dt) = 0;
    virtual bool IsRunning() = 0;
    virtual Renderer* CreateRenderer() = 0;

    WindowSpecification m_WindowSpecification;
};