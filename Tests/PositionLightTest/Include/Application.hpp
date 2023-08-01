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
        camera->SetAspectRatio(spec.Width / spec.Height);
        camera->SetPosition({ -20.0f, 0.0f, 0.0f });
        scenario->SetCamera(camera);

        auto redShader = Shader();
        redShader.Compile("Shaders/PositionalLight.vert", "Shaders/Red.frag");
        auto blueShader = Shader();
        blueShader.Compile("Shaders/PositionalLight.vert", "Shaders/Blue.frag");


        Entity* cube1 = new CubeEntity({ 0.0f, 0.0f, 20.0f }, 10.0f);
        cube1->GetMesh()->SetShader(redShader);
        scenario->AddEntity(cube1);

        Entity* cube2 = new CubeEntity({ 0.0f, 0.0f, -20.0f }, 10.0f);
        cube2->GetMesh()->SetShader(blueShader);
        scenario->AddEntity(cube2);


        renderer->Add(scenario);

        while (window->IsRunning())
        {
            Engine::Update();
        }
    }
};