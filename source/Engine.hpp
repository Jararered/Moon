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

private:
    std::vector<Window> m_Windows;

};