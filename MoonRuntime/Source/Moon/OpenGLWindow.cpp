#include "OpenGLWindow.hpp"

#include <glad/gl.h>
#include <glfw/glfw3.h>

#include "Input.hpp"

using namespace Moon;

OpenGLWindow::OpenGLWindow(const WindowSpecification& spec) : Window(spec)
{
    glfwInit();

#ifdef UNIX
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
#endif

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    p_GLFWwindow = glfwCreateWindow(spec.Width, spec.Height, spec.Title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(p_GLFWwindow);

    gladLoadGL(glfwGetProcAddress);

    if (spec.VSync)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
}

OpenGLWindow::~OpenGLWindow()
{
}

void OpenGLWindow::NewFrame()
{
    Input::PollEvents();
}

void OpenGLWindow::EndFrame()
{
    glfwSwapBuffers(p_GLFWwindow);
}

bool OpenGLWindow::IsRunning()
{
    return !glfwWindowShouldClose(p_GLFWwindow);
}
