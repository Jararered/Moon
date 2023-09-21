#pragma once

#include "WindowSpecification.hpp"

#include <vector>

class Window
{
public:
    Window(const WindowSpecification& spec) : m_WindowSpecification(spec){};
    virtual ~Window() = default;

    virtual bool IsRunning() = 0;
    virtual void NewFrame() = 0;
    virtual void EndFrame() = 0;

    WindowSpecification m_WindowSpecification;
};