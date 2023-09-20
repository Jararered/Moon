#include "Engine.hpp"

#include <filesystem>
#include <glfw/glfw3.h>

#include "OpenGLWindow.hpp"
#include "Scenario.hpp"

#include "Systems/CameraSystem.hpp"
#include "Systems/PhysicsSystem.hpp"
#include "Systems/RenderSystem.hpp"

#include "Component/Camera.hpp"
#include "Component/Mesh.hpp"
#include "Component/RigidBody.hpp"
#include "Component/Shader.hpp"
#include "Component/Texture.hpp"
#include "Component/Transform.hpp"

Scenario e_Scenario;

void Engine::Initialize()
{
    std::println("Initializing...");
    std::println("Current working directory: {}", std::filesystem::current_path().string());

    e_Scenario.Initialize();
    e_Scenario.RegisterComponent<Camera>();
    e_Scenario.RegisterComponent<Mesh>();
    e_Scenario.RegisterComponent<RigidBody>();
    e_Scenario.RegisterComponent<Shader>();
    e_Scenario.RegisterComponent<Texture>();
    e_Scenario.RegisterComponent<Transform>();

    m_SystemMap.emplace(1, e_Scenario.RegisterSystem<PhysicsSystem>());
    m_SystemMap.emplace(2, e_Scenario.RegisterSystem<CameraSystem>());
    m_SystemMap.emplace(3, e_Scenario.RegisterSystem<RenderSystem>());

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
    while (p_Window->IsRunning())
    {
        const auto frameStartTime = std::chrono::high_resolution_clock::now();

        if (p_Window)
        {
            p_Window->Update();
        }

        for (const auto [_, system] : m_SystemMap)
        {
            system->Update(m_DT);
        }

        const auto frameEndTime = std::chrono::high_resolution_clock::now();
        m_DT = std::chrono::duration<float, std::chrono::seconds::period>(frameEndTime - frameStartTime).count();
    }
}

std::shared_ptr<Window> Engine::CreateWindow(const WindowSpecification& spec)
{
    std::println("Creating window with size {}x{}", spec.Width, spec.Height);

    p_Window = std::make_shared<OpenGLWindow>(spec);
    return p_Window;
}