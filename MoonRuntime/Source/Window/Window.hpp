#pragma once

#include "Components/WindowSpecification.hpp"

#include <vector>

class Window
{
public:
    Window(const WindowSpecification& spec) : m_WindowSpecification(spec){};
    virtual ~Window() = default;

    virtual void Update(float dt) = 0;
    virtual bool IsRunning() = 0;

    WindowSpecification m_WindowSpecification;
};