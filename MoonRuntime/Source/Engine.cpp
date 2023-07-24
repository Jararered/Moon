#include "Engine.hpp"

#include "OpenGLWindow.hpp"
#include "MetalWindow.hpp"
#include "VulkanWindow.hpp"

#include <glfw/glfw3.h>
#include <iostream>

Engine::Engine()
{
}

Engine::~Engine()
{
    std::cout << "Engine::~Engine()\n";
}

void Engine::Update()
{
    double t0 = glfwGetTime();

    if (m_Windows.empty() == false)
    {
        for (auto& window : m_Windows)
        {
            window->Update(m_Dt);
        }
    }

    m_Dt = glfwGetTime() - t0;
}

std::shared_ptr<Window> Engine::CreateWindow(GraphicsAPI api)
{
    std::cout << "Engine::CreateWindow(): Creating window..." << std::endl;
    switch (api)
    {
    case OpenGL:
    {
        auto& window = m_Windows.emplace_back(std::make_shared<OpenGLWindow>());;
        return window;
    }
    case Vulkan:
    {
        std::cout << "Engine::CreateWindow(): Vulkan graphics API not implemented." << std::endl;
        return nullptr;
    }
    case Metal:
    {
        std::cout << "Engine::CreateWindow(): Metal graphics API not implemented." << std::endl;
        return nullptr;
    }
    default:
    {
        std::cout << "Engine::CreateWindow(): No graphics API selected." << std::endl;
        return nullptr;
    }
    }
}