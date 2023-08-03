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

    void UpdateTime();
    static double GetTime();
    std::string CurrentDirectory();

    Window* GetWindow(const WindowSpecification& spec);

protected:
    Window* p_Window = nullptr;

    float m_DeltaFrameTime = 0.0f;
    std::chrono::system_clock::time_point m_FrameStartTime;
    std::chrono::system_clock::time_point m_FrameEndTime;
};