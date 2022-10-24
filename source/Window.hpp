#pragma once

#include <vector>

#include <glfw/glfw3.h>

#include "Renderer.hpp"

class Window
{
public:
    Window();
    ~Window();

    void Update();
    Renderer& CreateRenderer();

private:
    std::vector<Renderer> m_Renderers;

    GLFWwindow *m_GLFWwindow = nullptr;
    int m_WindowHeight = 100;
    int m_WindowWidth = 100;
};