#pragma once

#include <chrono>
#include <string>

#include "Window.hpp"

class Engine
{
public:
    Engine();
    virtual ~Engine();

    virtual void Update();

protected:
    Window* p_Window = nullptr;
    float m_DeltaFrameTime = 0.0f;

public:
    static double GetTime();
    Window* GetWindow(const WindowSpecification& spec);
};