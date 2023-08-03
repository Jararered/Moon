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
        auto scenario = new Scenario;

        auto camera = new Camera2D;
        camera->SetAspectRatio(spec.Width / spec.Height);
        scenario->SetCamera(camera);

        auto shader = Shader();
        shader.Compile("Shaders/DirectionalLight.vert", "Shaders/DirectionalLight.frag");

        int size = 40;
        int countx = 16;
        int county = 9;
        for (int i = -countx; i < countx + 1; i++)
        {
            for (int j = -county; j < county + 1; j++)
            {
                Entity* entity = new SquareEntity({size * i, size * j, 0.0f}, size);
                entity->GetMesh()->SetShader(shader);
                scenario->AddEntity(entity);
            }
        }

        renderer->Add(scenario);

        while (window->IsRunning())
        {
            Update();
        }
    }
};