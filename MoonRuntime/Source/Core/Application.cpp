#include "Application.hpp"

#include "OpenGLWindow.hpp"

#include "Scenario/Scenario.hpp"

#include "System/CameraSystem.hpp"
#include "System/ControlSystem.hpp"
#include "System/PhysicsSystem.hpp"
#include "System/RenderSystem.hpp"
#include "System/ScriptSystem.hpp"

#include "Component/Camera.hpp"
#include "Component/Controller.hpp"
#include "Component/Mesh.hpp"
#include "Component/RigidBody.hpp"
#include "Component/Script.hpp"
#include "Component/Shader.hpp"
#include "Component/Texture.hpp"
#include "Component/Transform.hpp"

#include <filesystem>
#include <glfw/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

using namespace Moon;

void Application::Initialize()
{
    // Check if already initialized
    if (m_Status == ApplicationStatus::Initialized)
    {
        return;
    }

    m_Scenario = std::make_shared<Scenario>();

    m_Scenario->Initialize();

    m_Scenario->RegisterComponent<Camera>();
    m_Scenario->RegisterComponent<Controller>();
    m_Scenario->RegisterComponent<Mesh>();
    m_Scenario->RegisterComponent<RigidBody>();
    m_Scenario->RegisterComponent<Script>();
    m_Scenario->RegisterComponent<Shader>();
    m_Scenario->RegisterComponent<Texture>();
    m_Scenario->RegisterComponent<Transform>();

    // Emplace back systems in initialization and update order
    m_Systems.emplace(1, m_Scenario->RegisterSystem<ControlSystem>());
    m_Systems.emplace(2, m_Scenario->RegisterSystem<CameraSystem>());
    m_Systems.emplace(3, m_Scenario->RegisterSystem<ScriptSystem>());
    m_Systems.emplace(4, m_Scenario->RegisterSystem<PhysicsSystem>());
    m_Systems.emplace(5, m_Scenario->RegisterSystem<RenderSystem>());

    for (const auto [_, system] : m_Systems)
    {
        system->Register(m_Scenario);
    }

    for (const auto [_, system] : m_Systems)
    {
        system->Initialize();
    }

    m_Status = ApplicationStatus::Initialized;
}

void Application::Finalize()
{
}

void Application::CreateWindow(const WindowSpecification& spec)
{
    if (!m_Window)
    {
        m_Window = std::make_shared<OpenGLWindow>(spec);
    }

    if (m_Status == ApplicationStatus::Uninitialized)
    {
        Initialize();
    }
}

void Application::Start()
{
    if ((!m_Window) or (m_Status == ApplicationStatus::Uninitialized))
    {
        std::cout << "Application::Start: No window created. Returning...\n";
        return;
    }

    Loop();

    Finalize();
}

void Application::Loop()
{
    float dt = 0.0f;

    while (m_Window->IsRunning())
    {
        const auto frameStartTime = std::chrono::high_resolution_clock::now();

        m_Window->NewFrame();

        for (const auto [systemID, system] : m_Systems)
        {
            system->Update(dt);
        }

        m_Window->EndFrame();

        const auto frameEndTime = std::chrono::high_resolution_clock::now();
        dt = std::chrono::duration<float, std::chrono::seconds::period>(frameEndTime - frameStartTime).count();
    }
}