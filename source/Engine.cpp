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
    double ti = glfwGetTime();

    if (m_Windows.empty() == false)
    {
        for (auto &window : m_Windows)
        {
            window.Update(DT);
        }
    }

    double tf = glfwGetTime();
    DT = tf - ti;
}

Window &Engine::CreateWindow()
{
    return m_Windows.emplace_back();
}