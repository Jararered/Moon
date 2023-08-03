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
        camera->SetPosition({ 0.0f, 0.0f, 20.0f });
        scenario->SetCamera(camera);

        auto redShader = Shader();
        redShader.Compile("Shaders/PositionalLight.vert", "Shaders/Red.frag");
        Entity* cube1 = new CubeEntity({ 10.0f, 0.0f, 0.0f }, 10.0f);
        cube1->GetMesh()->SetShader(redShader);
        scenario->AddEntity(cube1);

        auto blueShader = Shader();
        blueShader.Compile("Shaders/PositionalLight.vert", "Shaders/Blue.frag");
        Entity* cube2 = new CubeEntity({ -10.0f, 0.0f, 0.0f }, 10.0f);
        cube2->GetMesh()->SetShader(blueShader);
        scenario->AddEntity(cube2);


        renderer->Add(scenario);

        while (window->IsRunning())
        {
            Engine::Update();
        }
    }
};