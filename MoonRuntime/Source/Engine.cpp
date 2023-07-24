#include "Engine.hpp"
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
        for (auto &window : m_Windows)
        {
            window.Update(m_Dt);
        }
    }

    m_Dt = glfwGetTime() - t0;
}

Window &Engine::CreateWindow()
{
    std::cout << "[Engine] Creating window..." << std::endl;
    return m_Windows.emplace_back();
}