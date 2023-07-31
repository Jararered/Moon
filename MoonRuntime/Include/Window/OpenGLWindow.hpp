#pragma once

#include <glfw/glfw3.h>

#include "Window.hpp"
#include "Renderer.hpp"

class OpenGLWindow : virtual public Window
{
public:
    OpenGLWindow(const WindowSpecification& spec);
    ~OpenGLWindow() override;

    void Update(float dt) override;
    bool IsRunning() override;
    Renderer* CreateRenderer() override;

private:
    Renderer* p_Renderer = nullptr;
    GLFWwindow* p_GLFWwindow = nullptr;
};