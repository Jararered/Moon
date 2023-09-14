#pragma once

#include <chrono>
#include <map>
#include <memory>
#include <string>

#include "System.hpp"
#include "Window.hpp"

class Engine
{
public:
    Engine() = default;
    virtual ~Engine() = default;

    void Initialize();
    void Update();
    void Finalize();

    void Start();

protected:
    float m_DT = 0.0f;

    std::shared_ptr<Window> p_Window;

    std::vector<std::shared_ptr<System>> m_Systems;
    std::map<unsigned int, std::shared_ptr<System>> m_SystemMap;

public:
    [[nodiscard]] static double GetTime();
    std::shared_ptr<Window> CreateWindow(const WindowSpecification& spec);
};