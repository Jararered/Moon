#include "Engine.hpp"

Engine::Engine()
{
}

Engine::~Engine()
{
    std::cout << "Engine::~Engine()\n";

}

void Engine::Update()
{
    if (m_Windows.empty() == false)
    {
        for (auto &window : m_Windows)
        {
            window.Update();
        }
    }
}

Window &Engine::CreateWindow()
{
    return m_Windows.emplace_back();
}