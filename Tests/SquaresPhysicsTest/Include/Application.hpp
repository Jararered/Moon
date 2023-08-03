#pragma once

#include <Moon.hpp>

#include "SquareEntity.hpp"

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

        auto window = Engine::GetWindow(spec);
        auto renderer = window->CreateRenderer();

        auto camera = new Camera2D;
        camera->SetAspectRatio(spec.Width / spec.Height);

        auto scenario = new Scenario;
        scenario->SetCamera(camera);

        auto shader = Shader();
        shader.Compile("Shaders/DirectionalLight.vert", "Shaders/DirectionalLight.frag");

        auto entity = new SquareEntity();
        entity->SetPosition({ 0.0f, 0.0f, 0.0f });
        entity->GetMesh()->SetShader(shader);
        scenario->AddEntity(entity);

        renderer->Add(scenario);

        while (window->IsRunning())
        {
            Update();
        }
    }
};