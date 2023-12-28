#include "OpenGLWindow.hpp"

#include <glad/gl.h>
#include <glfw/glfw3.h>

#include "Input.hpp"

// ImVec4 ToRGBA(int r, int g, int b, int a)
// {
//     // clang-format off
//     return ImVec4(static_cast<float>(r) / 255.0f,
//                   static_cast<float>(g) / 255.0f,
//                   static_cast<float>(b) / 255.0f,
//                   static_cast<float>(a));
//     // clang-format on
// }

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

    // IMGUI_CHECKVERSION();
    // ImGui::CreateContext();
    // ImGui::StyleColorsLight();
    // ImGuiIO& io = ImGui::GetIO();
    // io.Fonts->AddFontFromFileTTF("Resources/Fonts/segoeui.ttf", 18.0f);
    // ImGui_ImplGlfw_InitForOpenGL(p_GLFWwindow, true);
    // ImGui_ImplOpenGL3_Init("#version 150");
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
