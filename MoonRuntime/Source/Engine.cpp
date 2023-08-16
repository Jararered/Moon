#include "Engine.hpp"

#include <filesystem>
#include <glfw/glfw3.h>
#include <iostream>

#include "Components.hpp"
#include "Coordinator.hpp"
#include "OpenGLWindow.hpp"

Coordinator g_Coordinator;

void Engine::Initialize()
{
    std::filesystem::path cwd = std::filesystem::current_path();
    std::cout << "Engine::Engine(): Current working directory: " << cwd.string() << "\n";

    g_Coordinator.Initialize();
    g_Coordinator.RegisterComponent<Camera>();
    g_Coordinator.RegisterComponent<Gravity>();
    g_Coordinator.RegisterComponent<Mesh>();
    g_Coordinator.RegisterComponent<RigidBody>();
    g_Coordinator.RegisterComponent<Shader>();
    g_Coordinator.RegisterComponent<Collider>();
    g_Coordinator.RegisterComponent<Texture>();
    g_Coordinator.RegisterComponent<Transform>();

    p_RenderSystem = g_Coordinator.RegisterSystem<RenderSystem>();
    {
        Signature signature;
        signature.set(g_Coordinator.GetComponentType<Mesh>());
        signature.set(g_Coordinator.GetComponentType<Transform>());
        signature.set(g_Coordinator.GetComponentType<Shader>());
        signature.set(g_Coordinator.GetComponentType<Texture>());
        g_Coordinator.SetSystemSignature<RenderSystem>(signature);
    }

    p_CameraSystem = g_Coordinator.RegisterSystem<CameraSystem>();
    {
        Signature signature;
        signature.set(g_Coordinator.GetComponentType<Transform>());
        signature.set(g_Coordinator.GetComponentType<Camera>());
        g_Coordinator.SetSystemSignature<CameraSystem>(signature);
    }

    p_VerletSystem = g_Coordinator.RegisterSystem<VerletSystem>();
    {
        Signature signature;
        signature.set(g_Coordinator.GetComponentType<Transform>());
        signature.set(g_Coordinator.GetComponentType<Gravity>());
        signature.set(g_Coordinator.GetComponentType<RigidBody>());
        signature.set(g_Coordinator.GetComponentType<Collider>());
        g_Coordinator.SetSystemSignature<VerletSystem>(signature);
    }

    p_RenderSystem->Initialize();
    p_CameraSystem->Initialize();
    p_VerletSystem->Initialize();
}

void Engine::Update()
{
    if (p_Window)
        p_Window->Update(m_DeltaFrameTime);
}

Window* Engine::CreateWindow(const WindowSpecification& spec)
{
    std::cout << "Engine::CreateWindow(): Creating window\n";

    switch (spec.API)
    {
    case WindowSpecification::GraphicsAPI::OpenGL:
    {
        p_Window = new OpenGLWindow(spec);
        return p_Window;
    }
    case WindowSpecification::GraphicsAPI::Vulkan:
    {
        std::cout << "Engine::CreateWindow(): Vulkan graphics API not implemented\n";
        return nullptr;
    }
    case WindowSpecification::GraphicsAPI::Metal:
    {
        std::cout << "Engine::CreateWindow(): Metal graphics API not implemented\n";
        return nullptr;
    }
    default:
    {
        std::cout << "Engine::CreateWindow(): No graphics API selected\n";
        return nullptr;
    }
    }
}

double Engine::GetTime()
{
    return glfwGetTime();
}