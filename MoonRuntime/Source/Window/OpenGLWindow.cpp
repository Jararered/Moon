#include "OpenGLWindow.hpp"

#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <print>

#include "Input.hpp"

OpenGLWindow::OpenGLWindow(const WindowSpecification& spec) : Window(spec)
{
    if (!glfwInit())
    {
        std::print("Failed to initialize GLFW");
    }

#ifdef UNIX
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
#endif
    const int major(3), minor(3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    p_GLFWwindow = glfwCreateWindow(spec.Width, spec.Height, "Moon", NULL, NULL);
    if (!p_GLFWwindow)
    {
        std::print("Failed to create OpenGL window");
        glfwTerminate();
        return;
    }

    // Make the window's context current
    glfwMakeContextCurrent(p_GLFWwindow);

    const int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        std::print("Failed to initialize OpenGL context");
        glfwTerminate();
        return;
    }

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

    if (!Input::IsMouseCaptured() && Input::IsLeftClick())
        Input::CaptureCursor();

    if (Input::IsKeyPressed(KEY_ESCAPE) && Input::IsMouseCaptured())
        Input::ReleaseCursor();
}

bool OpenGLWindow::IsRunning()
{
    return !glfwWindowShouldClose(p_GLFWwindow);
}