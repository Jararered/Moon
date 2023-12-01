#pragma once

#include "Panel.hpp"

struct TestPanel : public Moon::Panel
{
    void Update()
    {
        ImGui::Begin("Test Panel");

        const auto& panel_pos = ImGui::GetWindowPos();
        ImGui::Text("Panel Position: %.0f, %.0f", panel_pos.x, panel_pos.y);

        const auto& panel_size = ImGui::GetWindowSize();
        ImGui::Text("Panel Size: %.0f x %.0f", panel_size.x, panel_size.y);

        ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::End();
    }
};