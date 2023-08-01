#pragma once

#include <Moon.hpp>

#include "ChunkEntity.hpp"
#include "SimpleLightEnvironment.hpp"

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
        renderer->Add(scenario);

        auto environment = new SimpleLightEnvironment;
        scenario->SetEnvironment(environment);

        auto camera = new Camera3D();
        camera->SetSpeed(50.0f);
        camera->SetPosition(glm::vec3(0.0f, 50.0f, 0.0f));
        camera->SetAspectRatio(spec.Width / spec.Height);
        scenario->SetCamera(camera);

        auto shader = Shader();
        shader.Compile("Shaders/DirectionalLight.vert", "Shaders/DirectionalLight.frag");

        int radius = 3;
        for (int x = -radius; x < radius + 1; x++)
        {
            for (int y = 0; y < 2; y++)
            {
                for (int z = -radius; z < radius + 1; z++)
                {
                    // ChunkManager::AddIndex(glm::vec3(x, y, z));
                    ChunkData* chunkData = new ChunkData(glm::vec3(x, y, z));
                    auto mesh = new ChunkMesh(chunkData);

                    Entity* entity = new ChunkEntity();
                    entity->SetMesh(mesh);
                    entity->GetMesh()->SetShader(shader);

                    scenario->AddEntity(entity);
                }
            }
        }

        while (window->IsRunning())
        {
            Update();
        }
    }
};