#include "Editor.hpp"

#include "Entity.hpp"
#include "Input.hpp"
#include "Mesh/Cube.hpp"
#include "Script/TestScript.hpp"

#include <glfw/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <print>

using namespace Moon;

void DrawStatistics()
{
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    static float f = 0.0f;
    static int counter = 0;

    ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

    ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f

    if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
}

void Editor::InitializeImGui()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    // io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
    // io.ConfigViewportsNoAutoMerge = true;
    // io.ConfigViewportsNoTaskBarIcon = true;

    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    // ImGuiStyle& style = ImGui::GetStyle();
    // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    // {
    //     style.WindowRounding = 0.0f;
    //     style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    // }

    auto context = glfwGetCurrentContext();
    ImGui_ImplGlfw_InitForOpenGL(context, true);

    // auto glsl_version = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
    ImGui_ImplOpenGL3_Init("#version 150");
}

void Editor::FinalizeImGui()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Editor::PreUpdate()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (Input::IsKeyPressed(Key::Escape))
        Input::ReleaseCursor();

    if (!Input::IsMouseCaptured() and Input::IsLeftClick() and !(ImGui::GetIO().WantCaptureMouse))
        Input::CaptureCursor();

    if (Input::IsKeyPressed(Key::Escape) and Input::IsMouseCaptured())
        Input::ReleaseCursor();
}

void Editor::PostUpdate()
{
    DrawStatistics();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
    // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    // {
    //     GLFWwindow* backup_current_context = glfwGetCurrentContext();
    //     ImGui::UpdatePlatformWindows();
    //     ImGui::RenderPlatformWindowsDefault();
    //     glfwMakeContextCurrent(backup_current_context);
    // }
}

void Editor::CreatePlatform()
{
    Entity entity = Entity(m_Scenario);
    entity.AddComponent<Transform>(Transform{.Position = {0, -5, 0}, .Rotation = {0, 0, 0}, .Scale = {10, 1, 10}});
    entity.AddComponent<RigidBody>(RigidBody{.Velocity = {0, 0, 0}, .Acceleration = {0, 0, 0}, .Mass = 0});
    entity.AddComponent<Mesh>(std::make_shared<TexturedCubeMesh>());
    entity.AddComponent<Texture>(Texture("Resources/Textures/debug.png"));
    entity.AddComponent<Shader>(Shader("Resources/Shaders/PositionNormalTexture.vert", "Resources/Shaders/Texture.frag"));
}
