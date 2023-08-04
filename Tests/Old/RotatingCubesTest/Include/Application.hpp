#pragma once

#include <Moon.hpp>

#include "CubeEntity.hpp"

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

        auto window = GetWindow(spec);
        auto renderer = window->CreateRenderer();
        auto scenario = new Scenario;

        auto camera = new Camera3D;
        camera->SetAspectRatio(spec.Width / spec.Height);
        scenario->SetCamera(camera);

        auto shader = Shader();
        shader.Compile("Shaders/DirectionalLight.vert", "Shaders/DirectionalLight.frag");

        int size = 25;
        int spacing = 50;
        int dimx = 5;
        int dimy = 5;
        int dimz = 5;
        for (int i = -dimx; i < dimx + 1; i++)
        {
            for (int j = -dimy; j < dimy + 1; j++)
            {
                for (int k = -dimz; k < dimz + 1; k++)
                {
                    Entity* entity = new CubeEntity({spacing * i, spacing * j, spacing * k}, size);
                    entity->GetMesh()->SetShader(shader);

                    scenario->AddEntity(entity);
                }
            }
        }

        renderer->Add(scenario);

        while (window->IsRunning())
        {
            Engine::Update();
        }
    }
};