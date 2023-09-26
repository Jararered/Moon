#pragma once

#include <chrono>
#include <map>
#include <memory>
#include <string>

#include "SystemInterface.hpp"
#include "Window.hpp"

class Engine
{
public:
    Engine() = default;
    virtual ~Engine() = default;

    std::shared_ptr<Window> CreateWindow(const WindowSpecification& spec);

    void Initialize();
    void Start();

protected:
    float m_DT = 0.0f;

    std::shared_ptr<Window> p_Window;

    std::vector<std::shared_ptr<SystemInterface>> m_Systems;
    std::map<unsigned int, std::shared_ptr<SystemInterface>> m_SystemMap;
};