#include "Engine.hpp"

#include <filesystem>
#include <glfw/glfw3.h>

#include "Coordinator.hpp"
#include "OpenGLWindow.hpp"

#include "Systems/CameraSystem.hpp"
#include "Systems/IndexSystem.hpp"
#include "Systems/PhysicsSystem.hpp"
#include "Systems/RenderSystem.hpp"

#include "Components/Camera.hpp"
#include "Components/Dynamics.hpp"
#include "Components/Index.hpp"
#include "Components/Mesh.hpp"
#include "Components/Shader.hpp"
#include "Components/Texture.hpp"
#include "Components/Transform.hpp"

Coordinator e_Coordinator;

void Engine::Initialize()
{
    std::println("Current working directory: {}", std::filesystem::current_path().string());

    e_Coordinator.Initialize();
    e_Coordinator.RegisterComponent<Camera>();
    e_Coordinator.RegisterComponent<Mesh>();
    e_Coordinator.RegisterComponent<Dynamics>();
    e_Coordinator.RegisterComponent<Shader>();
    e_Coordinator.RegisterComponent<Texture>();
    e_Coordinator.RegisterComponent<Transform>();
    e_Coordinator.RegisterComponent<Index>();

    m_SystemMap.emplace(1, e_Coordinator.RegisterSystem<IndexSystem>());
    m_SystemMap.emplace(2, e_Coordinator.RegisterSystem<PhysicsSystem>());
    m_SystemMap.emplace(3, e_Coordinator.RegisterSystem<CameraSystem>());
    m_SystemMap.emplace(4, e_Coordinator.RegisterSystem<RenderSystem>());

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

        Update();

        const auto frameEndTime = std::chrono::high_resolution_clock::now();
        m_DT = std::chrono::duration<float, std::chrono::seconds::period>(frameEndTime - frameStartTime).count();
    }
}

void Engine::Update()
{
    if (p_Window)
    {
        p_Window->Update(m_DT);
    }

    for (const auto [_, system] : m_SystemMap)
    {
        system->Update(m_DT);
    }
}

std::shared_ptr<Window> Engine::CreateWindow(const WindowSpecification& spec)
{
    std::println("Creating window with size {}x{}", spec.Width, spec.Height);

    p_Window = std::make_shared<OpenGLWindow>(spec);
    return p_Window;
}

double Engine::GetTime()
{
    return glfwGetTime();
}