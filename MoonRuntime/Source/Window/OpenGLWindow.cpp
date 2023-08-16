#include "OpenGLWindow.hpp"

#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>

#include "Input.hpp"

OpenGLWindow::OpenGLWindow(const WindowSpecification& spec) : Window(spec)
{
    if (!glfwInit())
        std::cout << "OpenGLWindow::OpenGLWindow(): Failed to initialize GLFW.\n";

#ifdef UNIX
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
#endif
    int major(3), minor(3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    p_GLFWwindow = glfwCreateWindow(spec.Width, spec.Height, "Moon (OpenGL 3.3)", NULL, NULL);
    if (!p_GLFWwindow)
    {
        std::cout << "OpenGLWindow::OpenGLWindow(): Failed to create OpenGL window.\n";
        glfwTerminate();
        return;
    }

    // Make the window's context current
    glfwMakeContextCurrent(p_GLFWwindow);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        std::cout << "OpenGLWindow::OpenGLWindow(): Failed to initialize OpenGL context.\n";
        glfwTerminate();
        return;
    }

    glfwSetWindowUserPointer(p_GLFWwindow, this);

    if (spec.VSync)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    // if (spec.EnableImgui)
    // {
    //     const char* glsl_version = "#version 150";
    //     IMGUI_CHECKVERSION();
    //     ImGui::CreateContext();
    //     ImGui::StyleColorsDark();
    //     ImGui_ImplGlfw_InitForOpenGL(p_GLFWwindow, true);
    //     ImGui_ImplOpenGL3_Init(glsl_version);
    // }
}

OpenGLWindow::~OpenGLWindow()
{
    glfwWindowShouldClose(p_GLFWwindow);
}

void OpenGLWindow::Update(float dt)
{
    glfwPollEvents();

    if (!Input::IsMouseCaptured() && Input::IsLeftClick() && !(m_WindowSpecification.EnableImgui && ImGui::GetIO().WantCaptureMouse))
        Input::CaptureCursor();

    if (Input::IsKeyPressed(KEY_ESCAPE) && Input::IsMouseCaptured())
        Input::ReleaseCursor();
}

bool OpenGLWindow::IsRunning()
{
    return !glfwWindowShouldClose(p_GLFWwindow);
}