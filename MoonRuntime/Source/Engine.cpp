#include "Engine.hpp"

#include <glfw/glfw3.h>

#include <filesystem>
#include <iostream>

#include "OpenGLWindow.hpp"

Engine::Engine() { std::cout << "Engine::Engine(): Current working directory: " << Engine::CurrentDirectory() << "\n"; }

Engine::~Engine() {}

void Engine::Update()
{
    m_FrameStartTime = std::chrono::high_resolution_clock::now();

    if (p_Window)
        p_Window->Update(m_DeltaFrameTime);

    m_FrameEndTime = std::chrono::high_resolution_clock::now();
    m_DeltaFrameTime = std::chrono::duration<float, std::chrono::seconds::period>(m_FrameEndTime - m_FrameStartTime).count();
}

double Engine::GetTime() { return glfwGetTime(); }

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

std::string Engine::CurrentDirectory()
{
    std::filesystem::path cwd = std::filesystem::current_path();
    return cwd.string();
}