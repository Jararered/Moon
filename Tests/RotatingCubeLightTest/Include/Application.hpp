#pragma once

#include <Moon.hpp>

#include "CubeEntity.hpp"
#include "RotatingLightEnvironment.hpp"

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

        auto window = GetWindow(spec);
        auto renderer = window->CreateRenderer();
        auto scenario = new Scenario;

        auto environment = new RotatingLightEnvironment;
        scenario->SetEnvironment(environment);

        auto camera = new Camera3D;
        scenario->SetCamera(camera);

        auto shader = Shader();
        shader.Compile("Shaders/DirectionalLight.vert", "Shaders/DirectionalLight.frag");

        int size = 25;
        int spacing = 50;
        int dimx = 3;
        int dimz = 3;
        for (int i = -dimx; i < dimx + 1; i++)
        {
            for (int k = -dimz; k < dimz + 1; k++)
            {
                Entity* entity = new CubeEntity({ spacing * i, 0.0f, spacing * k }, size);
                entity->GetMesh()->SetShader(shader);
                scenario->AddEntity(entity);
            }
        }

        renderer->Add(scenario);

        while (window->IsRunning())
        {
            Engine::Update();
        }
    }
};