#pragma once

#include <chrono>
#include <memory>
#include <string>

#include "Systems.hpp"
#include "Window.hpp"

class Engine
{
public:
    Engine() = default;
    virtual ~Engine() = default;

    void Initialize();
    virtual void Update();

protected:
    Window* p_Window = nullptr;
    float m_DeltaFrameTime = 0.0f;

    std::shared_ptr<CameraSystem> p_CameraSystem;
    std::shared_ptr<PhysicsSystem> p_PhysicsSystem;
    std::shared_ptr<RenderSystem> p_RenderSystem;
    std::shared_ptr<VerletSystem> p_VerletSystem;

public:
    static double GetTime();
    Window* CreateWindow(const WindowSpecification& spec);
};