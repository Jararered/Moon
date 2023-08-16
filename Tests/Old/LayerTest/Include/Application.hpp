#pragma once

#include <Moon.hpp>

#include <DebugInfoLayer.hpp>

class Application : public Engine
{
public:
    void Start()
    {
        WindowSpecification spec;
        spec.Width = 1280;
        spec.Height = 720;
        spec.VSync = true;
        spec.API = WindowSpecification::GraphicsAPI::OpenGL;
        spec.EnableImgui = true;

        auto window = CreateWindow(spec);
        auto layer = new DebugInfoLayer();
        window->AddLayer(layer);

        auto renderer = window->CreateRenderer();
        auto scenario = new Scenario;

        auto camera = new Camera3D;
        scenario->SetCamera(camera);

        camera->SetAspectRatio(spec.Width / spec.Height);
        camera->SetPosition({0.0f, 0.0f, 60.0f});

        renderer->SetScenario(scenario);

        while (window->IsRunning())
        {
            auto frameStartTime = std::chrono::high_resolution_clock::now();

            Update();

            auto frameEndTime = std::chrono::high_resolution_clock::now();
            m_DeltaFrameTime = std::chrono::duration<float, std::chrono::seconds::period>(frameEndTime - frameStartTime).count();
        }
    }
};