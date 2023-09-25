#include "Engine.hpp"

#include <filesystem>
#include <glfw/glfw3.h>

#include "OpenGLWindow.hpp"
#include "Scenario.hpp"

#include "Systems/CameraSystem.hpp"
#include "Systems/ControlSystem.hpp"
#include "Systems/PhysicsSystem.hpp"
#include "Systems/RenderSystem.hpp"
#include "Systems/ScriptSystem.hpp"

#include "Component/Camera.hpp"
#include "Component/Control.hpp"
#include "Component/Mesh.hpp"
#include "Component/RigidBody.hpp"
#include "Component/Script.hpp"
#include "Component/Shader.hpp"
#include "Component/Texture.hpp"
#include "Component/Transform.hpp"

Scenario e_Scenario;

void Engine::Initialize()
{
    e_Scenario.Initialize();
    e_Scenario.RegisterComponent<Camera>();
    e_Scenario.RegisterComponent<Control>();
    e_Scenario.RegisterComponent<Mesh>();
    e_Scenario.RegisterComponent<RigidBody>();
    e_Scenario.RegisterComponent<Script>();
    e_Scenario.RegisterComponent<Shader>();
    e_Scenario.RegisterComponent<Texture>();
    e_Scenario.RegisterComponent<Transform>();

    // Emplace back systems in initialization and update order
    m_SystemMap.emplace(1, e_Scenario.RegisterSystem<ControlSystem>());
    m_SystemMap.emplace(2, e_Scenario.RegisterSystem<CameraSystem>());
    m_SystemMap.emplace(3, e_Scenario.RegisterSystem<ScriptSystem>());
    m_SystemMap.emplace(4, e_Scenario.RegisterSystem<PhysicsSystem>());
    m_SystemMap.emplace(5, e_Scenario.RegisterSystem<RenderSystem>());

    for (const auto [_, system] : m_SystemMap)
    {
        system->Register();
    }

    for (const auto [_, system] : m_SystemMap)
    {
        system->Initialize();
    }
}

void Engine::Start()
{
    if (!p_Window)
        return;

    while (p_Window->IsRunning())
    {
        const auto frameStartTime = std::chrono::high_resolution_clock::now();

        p_Window->NewFrame();

        for (const auto [_, system] : m_SystemMap)
        {
            system->Update(m_DT);
        }

        p_Window->EndFrame();

        const auto frameEndTime = std::chrono::high_resolution_clock::now();
        m_DT = std::chrono::duration<float, std::chrono::seconds::period>(frameEndTime - frameStartTime).count();
    }
}

std::shared_ptr<Window> Engine::CreateWindow(const WindowSpecification& spec)
{
    p_Window = std::make_shared<OpenGLWindow>(spec);
    return p_Window;
}