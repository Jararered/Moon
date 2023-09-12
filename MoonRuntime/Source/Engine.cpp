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

Coordinator g_Coordinator;

void Engine::Initialize()
{
    std::println("Current working directory: {}", std::filesystem::current_path().string());

    g_Coordinator.Initialize();
    g_Coordinator.RegisterComponent<Camera>();
    g_Coordinator.RegisterComponent<Mesh>();
    g_Coordinator.RegisterComponent<Dynamics>();
    g_Coordinator.RegisterComponent<Shader>();
    g_Coordinator.RegisterComponent<Texture>();
    g_Coordinator.RegisterComponent<Transform>();
    g_Coordinator.RegisterComponent<Index>();

    m_SystemMap.emplace(1, g_Coordinator.RegisterSystem<IndexSystem>());
    m_SystemMap.emplace(2, g_Coordinator.RegisterSystem<PhysicsSystem>());
    m_SystemMap.emplace(3, g_Coordinator.RegisterSystem<CameraSystem>());
    m_SystemMap.emplace(4, g_Coordinator.RegisterSystem<RenderSystem>());

    for (const auto [_, system] : m_SystemMap)
    {
        system->Register();
    }

    for (const auto [_, system] : m_SystemMap)
    {
        system->Initialize();
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