#pragma once

#include <Moon.hpp>

namespace Moon
{

    class Editor final : public Application
    {
    public:
        void CreatePanels();
        void CreatePlatform();

    private:
        // std::unordered_map<std::string, std::shared_ptr<Panel>> m_Panels;
    };

}