#pragma once

#include <vector>

#include "Window.hpp"

class Engine
{
public:
    Engine();
    ~Engine();

    void Update();

    Window& CreateWindow();
    const float Dt() const {return m_Dt;};

private:
    std::vector<Window> m_Windows;
    float m_Dt = 0.0f;
};