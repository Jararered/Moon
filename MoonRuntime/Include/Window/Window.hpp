#pragma once

#include "Renderer.hpp"
#include "WindowSpecification.hpp"

class Window
{
public:
    Window() {};
    virtual ~Window() {};

    virtual void Update(float dt) = 0;
    virtual bool IsRunning() = 0;
    virtual Renderer* CreateRenderer() = 0;

protected:
    int m_Width = 1280;
    int m_Height = 720;
    bool m_VSync = true;
};