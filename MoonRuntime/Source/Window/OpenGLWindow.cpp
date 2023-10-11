#include "OpenGLWindow.hpp"

#include <glad/gl.h>
#include <glfw/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Input.hpp"

ImVec4 rgba(int r, int g, int b, int a)
{
    return ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, a);
}

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
    ImGui::StyleColorsLight();

    ImGuiStyle& style = ImGui::GetStyle();

    // style.Colors[ImGuiCol_Button] = rgba(255, 255, 255, 1);
    // style.Colors[ImGuiCol_ButtonHovered] = rgba(229, 229, 229, 1);
    // style.Colors[ImGuiCol_Text] = rgba(0, 0, 0, 1);
    // style.Colors[ImGuiCol_Header] = rgba(232, 234, 237, 1);
    // style.Colors[ImGuiCol_HeaderActive] = rgba(255, 255, 255, 1);
    // style.Colors[ImGuiCol_HeaderHovered];

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("Fonts/segoeui.ttf", 18.0f);

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