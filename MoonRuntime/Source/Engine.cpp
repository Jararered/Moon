#include "Engine.hpp"

#include <glfw/glfw3.h>

#include <filesystem>
#include <iostream>

#include "OpenGLWindow.hpp"

Engine::Engine()
{
    std::filesystem::path cwd = std::filesystem::current_path();
    std::cout << "Engine::Engine(): Current working directory: " << cwd.string() << "\n";
}

Engine::~Engine()
{
}

void Engine::Update()
{
    auto frameStartTime = std::chrono::high_resolution_clock::now();

    if (p_Window)
        p_Window->Update(m_DeltaFrameTime);

    auto frameEndTime = std::chrono::high_resolution_clock::now();
    m_DeltaFrameTime = std::chrono::duration<float, std::chrono::seconds::period>(frameEndTime - frameStartTime).count();
}

Window* Engine::GetWindow(const WindowSpecification& spec)
{
    std::cout << "Engine::GetWindow(): Creating window\n";

    switch (spec.API)
    {
    case WindowSpecification::GraphicsAPI::OpenGL:
    {
        p_Window = new OpenGLWindow(spec);
        return p_Window;
    }
    case WindowSpecification::GraphicsAPI::Vulkan:
    {
        std::cout << "Engine::GetWindow(): Vulkan graphics API not implemented\n";
        return nullptr;
    }
    case WindowSpecification::GraphicsAPI::Metal:
    {
        std::cout << "Engine::GetWindow(): Metal graphics API not implemented\n";
        return nullptr;
    }
    default:
    {
        std::cout << "Engine::GetWindow(): No graphics API selected\n";
        return nullptr;
    }
    }
}

double Engine::GetTime()
{
    return glfwGetTime();
}