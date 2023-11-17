#pragma once

#include <Core/Panel.hpp>

class StatisticsPanel final : public Moon::Panel
{
public:
    ~StatisticsPanel() override = default;

    void Update() override
    {
        ImGui::Begin("Statistics", NULL, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
};