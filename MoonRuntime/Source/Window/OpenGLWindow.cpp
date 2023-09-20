#include "OpenGLWindow.hpp"

#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <print>

#include "Input.hpp"

OpenGLWindow::OpenGLWindow(const WindowSpecification& spec) : Window(spec)
{
#ifdef UNIX
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
#endif
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwInit();
    p_GLFWwindow = glfwCreateWindow(spec.Width, spec.Height, spec.Title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(p_GLFWwindow);

    gladLoadGL(glfwGetProcAddress);
}

OpenGLWindow::~OpenGLWindow()
{
}

void OpenGLWindow::Update()
{
    glfwPollEvents();

    if (!Input::IsMouseCaptured() and Input::IsLeftClick())
        Input::CaptureCursor();

    if (Input::IsKeyPressed(KEY_ESCAPE) and Input::IsMouseCaptured())
        Input::ReleaseCursor();
}

bool OpenGLWindow::IsRunning()
{
    return not glfwWindowShouldClose(p_GLFWwindow);
}