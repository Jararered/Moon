#pragma once

#include <vector>
#include <glfw/glfw3.h>

#include "Window.hpp"
#include "Renderer.hpp"

class OpenGLWindow : public Window
{
public:
    OpenGLWindow();
    ~OpenGLWindow() override;

    void Update(float dt) override;
    bool IsRunning() override;
    Renderer& CreateRenderer() override;

private:
    std::vector<Renderer> m_Renderers;

    GLFWwindow *m_GLFWwindow = nullptr;
    int m_WindowHeight = 720;
    int m_WindowWidth = 1280;
};