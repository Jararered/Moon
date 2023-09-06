#include "Engine.hpp"

#include <filesystem>
#include <glfw/glfw3.h>
#include <iostream>

#include "Coordinator.hpp"
#include "Debug.hpp"
#include "OpenGLWindow.hpp"

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
    std::filesystem::path cwd = std::filesystem::current_path();
    DebugOutput("Current working directory: " << cwd.string());

    g_Coordinator.Initialize();
    g_Coordinator.RegisterComponent<Camera>();
    g_Coordinator.RegisterComponent<Mesh>();
    g_Coordinator.RegisterComponent<Dynamics>();
    g_Coordinator.RegisterComponent<Shader>();
    g_Coordinator.RegisterComponent<Texture>();
    g_Coordinator.RegisterComponent<Transform>();

    m_Systems.emplace_back(g_Coordinator.RegisterSystem<CameraSystem>());
    m_Systems.emplace_back(g_Coordinator.RegisterSystem<PhysicsSystem>());
    m_Systems.emplace_back(g_Coordinator.RegisterSystem<RenderSystem>());

    for (const auto system : m_Systems)
    {
        system->Register();
    }

    for (const auto system : m_Systems)
    {
        system->Initialize();
    }
}

void Engine::Update()
{
    if (p_Window)
    {
        p_Window->Update(m_DeltaFrameTime);
    }

    for (const auto system : m_Systems)
    {
        system->Update(m_DeltaFrameTime);
    }
}

std::shared_ptr<Window> Engine::CreateWindow(const WindowSpecification& spec)
{
    DebugOutput("Creating window");

    switch (spec.API)
    {
    case WindowSpecification::GraphicsAPI::OpenGL:
    {
        p_Window = std::make_shared<OpenGLWindow>(spec);
        return p_Window;
    }
    case WindowSpecification::GraphicsAPI::Vulkan:
    {
        DebugOutput("Vulkan graphics API not implemented");
        return nullptr;
    }
    case WindowSpecification::GraphicsAPI::Metal:
    {
        DebugOutput("Metal graphics API not implemented");
        return nullptr;
    }
    default:
    {
        DebugOutput("No graphics API selected");
        return nullptr;
    }
    }
}

double Engine::GetTime()
{
    return glfwGetTime();
}