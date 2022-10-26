#pragma once

#include <vector>

#include "Window.hpp"

class Engine
{
public:
    Engine();
    ~Engine();

    void Update();
    bool IsRunning();
    Window& CreateWindow();

private:
    std::vector<Window> m_Windows;
    float DT = 0.0f;
};