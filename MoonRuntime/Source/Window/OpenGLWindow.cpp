#include "OpenGLWindow.hpp"

#include <iostream>
#include <glad/gl.h>

#include "input/Input.hpp"

OpenGLWindow::OpenGLWindow(const WindowSpecification& spec)
    : Window(spec)
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
    p_GLFWwindow = glfwCreateWindow(spec.Width, spec.Height, "Moon (OpenGL 3.3)", NULL, NULL);
    if (!p_GLFWwindow)
    {
        std::cout << "OpenGLWindow::OpenGLWindow(): Failed to create OpenGL window.\n";
        glfwTerminate();
    }

    // Make the window's context current
    glfwMakeContextCurrent(p_GLFWwindow);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
        std::cout << "OpenGLWindow::OpenGLWindow(): Failed to initialize OpenGL context.\n";

    glfwSetWindowUserPointer(p_GLFWwindow, this);

    if (spec.VSync)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
}

OpenGLWindow::~OpenGLWindow()
{
    glfwWindowShouldClose(p_GLFWwindow);
}

void OpenGLWindow::Update(float dt)
{
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

    if (p_Renderer)
        p_Renderer->Update(dt);
}

bool OpenGLWindow::IsRunning()
{
    return !glfwWindowShouldClose(p_GLFWwindow);
}

Renderer* OpenGLWindow::CreateRenderer()
{
    p_Renderer = new Renderer;
    return p_Renderer;
}