#pragma once

#include <chrono>
#include <memory>
#include <string>

#include "Window.hpp"

#include "Systems/CameraSystem.hpp"
#include "Systems/PhysicsSystem.hpp"
#include "Systems/RenderSystem.hpp"

class Engine
{
public:
    Engine() = default;
    virtual ~Engine() = default;

    void Initialize();
    virtual void Update();

protected:
    float m_DeltaFrameTime = 0.0f;

    std::shared_ptr<Window> p_Window;

    std::vector<std::shared_ptr<System>> m_Systems;

public:
    static double GetTime();
    std::shared_ptr<Window> CreateWindow(const WindowSpecification& spec);
};