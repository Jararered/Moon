#pragma once

#include <vector>
#include <memory>

#include "Window.hpp"

class Engine
{
public:
    Engine();
    ~Engine();

    void Update();

    std::shared_ptr<Window> CreateWindow(GraphicsAPI api);
    const float Dt() const { return m_Dt; };

private:
    std::vector<std::shared_ptr<Window>> m_Windows;
    float m_Dt = 0.0f;
};