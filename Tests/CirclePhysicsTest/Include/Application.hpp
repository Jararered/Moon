#pragma once

#include <Moon.hpp>

#include "CircleCollider.hpp"
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
        shader.Compile("Shaders/Texture.vert", "Shaders/Texture.frag");

        auto texture = Texture("Textures/circle.png");

        for (int i = -5; i < 5; i++)
        {
            glm::vec3 position = {i * 100.0f, 0.0f, 0.0f};
            glm::vec3 velocity = {i * 73.0f, i * 100.0f, 0.0f};
            float size = 50.0f;

            auto entity = new SquareEntity();
            auto mesh = new SquareMesh(size);
            auto collider = new CircleCollider(size / 2.0f);

            entity->SetPosition(position);
            entity->SetVelocity(velocity);
            entity->SetMesh(mesh);
            entity->GetMesh()->SetShader(shader);
            entity->GetMesh()->SetTexture(texture);
            entity->SetCollider(collider);

            scenario->AddEntity(entity);
        }

        renderer->Add(scenario);

        while (window->IsRunning())
        {
            Update();
        }
    }
};