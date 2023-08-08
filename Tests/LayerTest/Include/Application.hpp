#pragma once

#include <Moon.hpp>

class Application : public Engine
{
public:
    void Start()
    {
        WindowSpecification spec;
        spec.Width = 1980;
        spec.Height = 1080;
        spec.VSync = true;
        spec.API = WindowSpecification::GraphicsAPI::OpenGL;
        spec.EnableImgui = true;

        auto window = CreateWindow(spec);
        auto layer = Layer();
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
            Engine::Update();
        }
    }
};