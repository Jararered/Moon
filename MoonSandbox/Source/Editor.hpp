#pragma once

#include <Application.hpp>

namespace Moon
{

    class Editor final : public Application
    {
    public:
        void InitializeImGui();
        void FinalizeImGui();

        void CreatePlatform();

        void PreUpdate() override;
        void PostUpdate() override;
    };

}