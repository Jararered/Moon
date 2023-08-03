#pragma once

#include <string>

#include "Window.hpp"

class Engine
{
public:
    Engine();
    virtual ~Engine();

public:
    virtual void Update();
    void UpdateTime();
    static double GetTime();
    std::string CurrentDirectory();

    Window* GetWindow(const WindowSpecification& spec);

protected:
    Window* p_Window = nullptr;

    float m_DeltaFrameTime = 0.0f;
    float m_LastFrameTime = 0.0f;
    float m_TempAverage = 0.0f;
    u_int64_t m_FrameCount = 0;
    u_int8_t m_FrameCounter = 0;
};