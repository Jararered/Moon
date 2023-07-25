#include "OpenGLWindow.hpp"

#include <iostream>
#include <glad/gl.h>

#include "input/Input.hpp"

OpenGLWindow::OpenGLWindow()
{
    if (!glfwInit())
        std::cout << "OpenGLWindow::OpenGLWindow(): Failed to initialize GLFW.\n";

#ifdef UNIX
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
#endif
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    m_GLFWwindow = glfwCreateWindow(m_WindowWidth, m_WindowHeight, "Moon (OpenGL 3.3)", NULL, NULL);
    if (!m_GLFWwindow)
    {
        std::cout << "OpenGLWindow::OpenGLWindow(): Failed to create OpenGL window.\n";
        glfwTerminate();
    }

    // Make the window's context current
    glfwMakeContextCurrent(m_GLFWwindow);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
        std::cout << "OpenGLWindow::OpenGLWindow(): Failed to initialize OpenGL context.\n";

    glfwSetWindowUserPointer(m_GLFWwindow, this);

    glfwSwapInterval(1);
}

OpenGLWindow::~OpenGLWindow()
{
    glfwWindowShouldClose(m_GLFWwindow);
}

void OpenGLWindow::Update(float dt)
{
    if (m_Renderers.empty() == false)
    {
        for (auto &renderer : m_Renderers)
        {
            renderer.Update(dt);
        }
    }

    glfwPollEvents();

    if (!Input::IsMouseCaptured())
    {
        if (Input::IsLeftClick())
        {
            Input::CaptureCursor();
        }
    }

    if (Input::IsKeyPressed(KEY_ESCAPE) && Input::IsMouseCaptured())
    {
        Input::ReleaseCursor();
    }
}

bool OpenGLWindow::IsRunning()
{
    return !glfwWindowShouldClose(m_GLFWwindow);
}

Renderer &OpenGLWindow::CreateRenderer()
{
    return m_Renderers.emplace_back();
}