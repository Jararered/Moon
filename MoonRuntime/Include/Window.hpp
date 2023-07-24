#pragma once

#include <vector>
#include <glfw/glfw3.h>

#include "Renderer.hpp"

class Window
{
public:
    Window();
    ~Window();

    void Update(float dt);
    bool IsRunning();
    Renderer& CreateRenderer();

private:
    std::vector<Renderer> m_Renderers;

    GLFWwindow *m_GLFWwindow = nullptr;
    int m_WindowHeight = 720;
    int m_WindowWidth = 1280;
};