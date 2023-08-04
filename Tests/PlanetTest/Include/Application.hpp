#pragma once

#include <Moon.hpp>

#include "ChunkEntity.hpp"

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

        auto camera = new Camera3D();
        camera->SetAspectRatio(spec.Width / spec.Height);
        scenario->SetCamera(camera);

        auto shader = Shader();
        shader.Compile("Shaders/DirectionalLight.vert", "Shaders/DirectionalLight.frag");

        int radius = 4;
        for (int x = -radius; x < radius + 1; x++)
        {
            for (int y = -radius; y < radius + 1; y++)
            {
                for (int z = -radius; z < radius + 1; z++)
                {
                    Entity* entity = new ChunkEntity();
                    entity->SetPosition(glm::vec3(x, y, z));

                    ChunkData* chunkData = new ChunkData(glm::vec3(x, y, z));
                    auto mesh = new ChunkMesh(chunkData);
                    entity->SetMesh(mesh);
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