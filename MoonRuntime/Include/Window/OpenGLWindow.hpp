#pragma once

#include "Renderer.hpp"
#include "Window.hpp"

struct GLFWwindow;

class OpenGLWindow : public Window
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