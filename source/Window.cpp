#include "Window.hpp"

#include <iostream>
#include <glad/gl.h>

Window::Window()
{
    if (!glfwInit())
    {
        std::cout << "[Error] Failed to initialize GLFW.\n";
    }

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);

    // Create a windowed mode window and its OpenGL context
    m_GLFWwindow = glfwCreateWindow(m_WindowWidth, m_WindowHeight, "Moon (OpenGL 3.3)", NULL, NULL);
    if (!m_GLFWwindow)
    {
        std::cout << "[Error] Failed to create OpenGL window.\n";
        glfwTerminate();
    }

    // Make the window's context current
    glfwMakeContextCurrent(m_GLFWwindow);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        std::cout << "[Error] Failed to initialize OpenGL context.\n";
    }

    glfwSetWindowUserPointer(m_GLFWwindow, this);

    glfwSwapInterval(1);
}

Window::~Window()
{
    std::cout << "Window::~Window()\n";
    glfwWindowShouldClose(m_GLFWwindow);
}

void Window::Update()
{
    if (m_Renderers.empty() == false)
    {
        for (auto &renderer : m_Renderers)
        {
            renderer.Update();
        }
    }

    glfwPollEvents();
}

Renderer& Window::CreateRenderer()
{
    return m_Renderers.emplace_back();
}