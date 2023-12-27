#pragma once

#include <Application.hpp>

namespace Moon
{

    class Editor final : public Application
    {
    public:
        void InitializeImGui();
        void CreatePanels();
        void CreatePlatform();

    private:
        // std::unordered_map<std::string, std::shared_ptr<Panel>> m_Panels;
    };

}