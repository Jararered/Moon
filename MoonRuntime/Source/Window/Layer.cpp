#include "Layer.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

void Layer::Update()
{
    ImGuiIO& io = ImGui::GetIO();

    ImGui::Text("This is some useful text.");

    float f = 0.0f;
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

    int counter = 0;
    if (ImGui::Button("Button"))
        counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
}