#include "Engine.hpp"

#include "OpenGLWindow.hpp"

#include <glfw/glfw3.h>
#include <filesystem>
#include <iostream>

Engine::Engine()
{
    std::cout << "Engine::Engine(): Current working directory: " << Engine::CurrentDirectory() << "\n";
}

Engine::~Engine()
{
}

void Engine::Update()
{
    UpdateTime();

    if (p_Window)
        p_Window->Update(m_DeltaFrameTime);
}

void Engine::UpdateTime()
{
    float currentFrameTime = glfwGetTime();
    m_DeltaFrameTime = currentFrameTime - m_LastFrameTime;
    m_LastFrameTime = currentFrameTime;
}

double Engine::GetTime()
{
    return glfwGetTime();
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

std::string Engine::CurrentDirectory()
{
    std::filesystem::path cwd = std::filesystem::current_path();
    return cwd.string();
}