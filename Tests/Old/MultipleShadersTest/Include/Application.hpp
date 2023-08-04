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
        camera->SetPosition({0.0f, 0.0f, 20.0f});
        scenario->SetCamera(camera);

        auto colorShader = Shader();
        colorShader.Compile("Shaders/PositionColor.vert", "Shaders/PositionColor.frag");

        for (int x = -100.0f; x < 100.0f; x += 10.0f)
        {
            for (int z = -100.0f; z < 100.0f; z += 10.0f)
            {
                Entity* cube = new CubeEntity({x * 2.0f, 0.0f, z * 2.0f}, 10.0f, {x / 100.0f, -x / 100.0f + -z / 100.0f, z / 100.0f});
                cube->GetMesh()->SetShader(colorShader);
                scenario->AddEntity(cube);
            }
        }

        renderer->Add(scenario);

        while (window->IsRunning())
        {
            Engine::Update();
        }
    }
};