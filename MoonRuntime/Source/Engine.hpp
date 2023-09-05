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

    std::shared_ptr<CameraSystem> p_CameraSystem;
    std::shared_ptr<PhysicsSystem> p_PhysicsSystem;
    std::shared_ptr<RenderSystem> p_RenderSystem;

public:
    static double GetTime();
    std::shared_ptr<Window> CreateWindow(const WindowSpecification& spec);
};