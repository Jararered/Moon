#pragma once

#include <Core/Panel.hpp>

class CreateEntityPanel final : public Moon::Panel
{
public:
    ~CreateEntityPanel() override = default;

    void Update() override
    {
        ImGui::Begin();

        ImGui::End();
    }
};
