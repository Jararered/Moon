#include "Engine.hpp"

#include "OpenGLWindow.hpp"
#include "Scenario.hpp"

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
#include "Component/Test.hpp"
#include "Component/Texture.hpp"
#include "Component/Transform.hpp"

#include <filesystem>
#include <glfw/glfw3.h>
#include <imgui.h>

namespace Moon
{
void Engine::Initialize()
{
    if (m_Status == EngineStatus::Initialized)
        return;

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
    m_Scenario->RegisterComponent<Test>();

    // Emplace back systems in initialization and update order
    m_SystemMap.emplace(1, m_Scenario->RegisterSystem<ControlSystem>());
    m_SystemMap.emplace(2, m_Scenario->RegisterSystem<CameraSystem>());
    m_SystemMap.emplace(3, m_Scenario->RegisterSystem<ScriptSystem>());
    m_SystemMap.emplace(4, m_Scenario->RegisterSystem<PhysicsSystem>());
    m_SystemMap.emplace(5, m_Scenario->RegisterSystem<RenderSystem>());

    for (const auto [_, system] : m_SystemMap)
    {
        system->Register(m_Scenario);
    }

    for (const auto [_, system] : m_SystemMap)
    {
        system->Initialize();
    }

    m_Status = EngineStatus::Initialized;
}

void Engine::Start()
{
    if (!p_Window or m_Status == EngineStatus::Uninitialized)
        return;

    while (p_Window->IsRunning())
    {
        const auto frameStartTime = std::chrono::high_resolution_clock::now();

        p_Window->NewFrame();

        for (const auto [systemID, system] : m_SystemMap)
        {
            system->Update(m_DT);
        }

        UpdateUI();

        p_Window->EndFrame();

        const auto frameEndTime = std::chrono::high_resolution_clock::now();
        m_DT = std::chrono::duration<float, std::chrono::seconds::period>(frameEndTime - frameStartTime).count();
    }
}

void Engine::CreateWindow(const WindowSpecification& spec)
{
    if (!p_Window)
        p_Window = std::make_shared<OpenGLWindow>(spec);

    if (m_Status == EngineStatus::Uninitialized)
        Initialize();
}

void Engine::UpdateUI()
{
    // Engine Systems UI
    ImGui::Begin("Engine Systems", NULL, ImGuiWindowFlags_AlwaysAutoResize);
    for (const auto [systemID, system] : m_SystemMap)
    {
        if (ImGui::CollapsingHeader(system->m_Name.c_str()))
        {
            ImGui::PushItemWidth(150);
            system->UpdateUI();
        }
    }
    ImGui::End();
}
}