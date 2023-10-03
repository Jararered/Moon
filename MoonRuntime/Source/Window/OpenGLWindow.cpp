#include "OpenGLWindow.hpp"

#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Input.hpp"

OpenGLWindow::OpenGLWindow(const WindowSpecification& spec) : Window(spec)
{
    glfwInit();

#ifdef UNIX
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
#endif

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    p_GLFWwindow = glfwCreateWindow(m_WindowSpecification.Width, m_WindowSpecification.Height, m_WindowSpecification.Title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(p_GLFWwindow);

    gladLoadGL(glfwGetProcAddress);

    if (m_WindowSpecification.VSync)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(p_GLFWwindow, true);
    ImGui_ImplOpenGL3_Init("#version 150");
}

OpenGLWindow::~OpenGLWindow()
{
}

void OpenGLWindow::NewFrame()
{
    Input::PollEvents();

    if (Input::IsKeyPressed(Key::Escape))
        Input::ReleaseCursor();

    if (!Input::IsMouseCaptured() and Input::IsLeftClick() and !(ImGui::GetIO().WantCaptureMouse))
        Input::CaptureCursor();

    if (Input::IsKeyPressed(Key::Escape) and Input::IsMouseCaptured())
        Input::ReleaseCursor();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void OpenGLWindow::EndFrame()
{
    ImGui::Begin("Statistics", NULL, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(p_GLFWwindow);
}

bool OpenGLWindow::IsRunning()
{
    return not glfwWindowShouldClose(p_GLFWwindow);
}