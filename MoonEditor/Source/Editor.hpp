#pragma once

#include <Moon.hpp>

#include "Panel/TestPanel.hpp"
#include "Script/TestScript.hpp"

#include "Mesh/Cube.hpp"

namespace Moon
{

    class Editor final : public Application
    {
    public:
        void CreatePanels();
        void CreatePlatform();

    private:
        std::unordered_map<std::string, std::shared_ptr<Panel>> m_Panels;
    };

}