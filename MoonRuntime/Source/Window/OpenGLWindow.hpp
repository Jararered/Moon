#pragma once

#include "Window.hpp"

struct GLFWwindow;

class OpenGLWindow final : public Window
{
public:
    OpenGLWindow(const WindowSpecification& spec);
    ~OpenGLWindow() override;

    void NewFrame() override;
    void EndFrame() override;

    [[nodiscard]] bool IsRunning() override;

private:
    GLFWwindow* p_GLFWwindow = nullptr;
};