#pragma once

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
    Renderer* CreateRenderer() override;

private:
    Renderer* p_Renderer = nullptr;
    GLFWwindow* p_GLFWwindow = nullptr;
};