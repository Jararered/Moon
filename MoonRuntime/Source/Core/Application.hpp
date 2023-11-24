#pragma once

#include "Scenario.hpp"
#include "SystemInterface.hpp"
#include "Window.hpp"

#include "Component/Camera.hpp"
#include "Component/Controller.hpp"
#include "Component/Mesh.hpp"
#include "Component/Panel.hpp"
#include "Component/RigidBody.hpp"
#include "Component/Script.hpp"
#include "Component/Shader.hpp"
#include "Component/Texture.hpp"
#include "Component/Transform.hpp"

#include <chrono>
#include <map>
#include <memory>
#include <string>

namespace Moon
{

    enum ApplicationStatus
    {
        Initialized,
        Uninitialized
    };

    class Application
    {
    public:
        Application() = default;
        virtual ~Application() = default;

        void CreateWindow(const WindowSpecification& spec);
        void Start();

    private:
        void Initialize();
        void Finalize();
        void Loop();

    protected:
        std::shared_ptr<Window> m_Window;
        std::shared_ptr<Scenario> m_Scenario;

        ApplicationStatus m_Status = ApplicationStatus::Uninitialized;

        std::map<unsigned int, std::shared_ptr<SystemInterface>> m_Systems;
        std::unordered_map<std::string, std::shared_ptr<Panel>> m_Panels;

        std::unordered_map<std::string, Mesh> m_MeshLibrary;
        std::unordered_map<std::string, Script> m_ScriptLibrary;
        std::unordered_map<std::string, Texture> m_TextureLibrary;
        std::unordered_map<std::string, Shader> m_ShaderLibrary;
    };

}